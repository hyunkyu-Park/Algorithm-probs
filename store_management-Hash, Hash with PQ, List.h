#include <unordered_map>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

struct Buy{
    int product;  
    int price; 
    int quantity;
    int rest; 
};

unordered_map<int, Buy> buys;
unordered_map<int, int> product_remain; //number of remaining items for each product
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q[601]; 
unordered_map<int, int> qindex; //key: mProduct, value: index of the q
int lastQindex;

struct Sell{
	bool isValid;
	int product; 
	list<pair<int, int>>::iterator itBegin, itEnd;
};

unordered_map<int, Sell> sells;
list<pair<int, int>> sell_history;


void init() {
	buys.clear();
	product_remain.clear();
	qindex.clear();
	sells.clear();
	sell_history.clear();

	for(int i=1; i<lastQindex; ++i){
		while(!q[i].empty()){
			q[i].pop();
		}
	}
	lastQindex = 0;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {

	buys[bId] = {mProduct, mPrice, mQuantity, mQuantity}; //add new information
	
	product_remain[mProduct] += mQuantity;//change total quantity of the product

	if(qindex[mProduct] ==0){//if its a new product
		qindex[mProduct] = ++lastQindex;
	}
	q[qindex[mProduct]].push({mPrice, bId});
	return product_remain[mProduct];
}

int cancel(int bId) {
	auto it = buys.find(bId);
	if(it ==buys.end() || it->second.quantity != it->second.rest) { //product is not in the buying list or quantity is not equal to rest
		return -1;
	}

	product_remain[it->second.product] -= it->second.rest; //remove the number of remaining items from product_remain
	it->second.rest =0;

	return product_remain[it->second.product];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
	//if total amount of items of product is less than Quantity, fail to sell
	if(product_remain[mProduct] < mQuantity){
		return -1;
	}

	product_remain[mProduct] -= mQuantity; //change total amount of items

	// sells[sId] = {true, mProduct, sell_history.begin(), sell_history.begin()}; 
	//새로운 판매 정보 생성
	sells[sId].isValid = true;
	sells[sId].product = mProduct;
	sells[sId].itEnd = sell_history.begin();

	//Products purchased at the cheapest price and products with the smallest BId value are sold first
	int index = qindex[mProduct];
	int profit = 0;
	while(mQuantity > 0){
		int bId = q[index].top().second;
		int cnt = min(buys[bId].rest, mQuantity);
		buys[bId].rest -= cnt;
		mQuantity -= cnt;
		profit += (mPrice - buys[bId].price) * cnt;
		sell_history.push_front({bId, cnt});
		if(buys[bId].rest <=0){
			q[index].pop();
		}
	}
	sells[sId].itBegin = sell_history.begin();

	return profit;
}

int refund(int sId) {
	//Refund failed if there is no history of selling with sId or if the ID has already been refunded
	if(!sells[sId].isValid){
		return -1;
	}
	

	//refund the product selling with sId
	int cnt = 0;
	int index = qindex[sells[sId].product];
	sells[sId].isValid = false;
	for(auto it = sells[sId].itBegin; it!=sells[sId].itEnd; it++){
		if(buys[it->first].rest ==0){
			q[index].push({buys[it->first].price, it->first});
		}
		buys[it->first].rest += it->second;
		cnt += it->second;
	}

	//change the total amount of the product
	product_remain[sells[sId].product] += cnt;

	//return the total number of products refunded
	return cnt;
}