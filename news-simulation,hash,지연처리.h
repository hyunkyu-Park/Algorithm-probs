//지연 처리

#include <unordered_map>
#include <vector>
#include <queue>
#define USER_SIZE 501
#define CHANNEL_SIZE 501
#define NEWS_SIZE 30001

using namespace std;

struct NEWS{
	int release_time;
	int news_id;
	int channel_id;
	bool canceled;

	bool operator() (const NEWS* a, const NEWS* b) const
	{
		if (a->release_time == b->release_time)
			return a->news_id > b->news_id;
		return a->release_time > b->release_time;
	}
};

unordered_map<int, int> user_info; //Hash to change uID to idx for user_pool
unordered_map<int, int> news_info; //Hash to change NewsID to idx for news_pool
unordered_map<int, int> channel_info; //Hash to change ChannelID to idx for channel_pool
priority_queue<NEWS*, vector<NEWS*>, NEWS> news_queue; //PQ that stores NEWS pointer

//NEWS are only stored in news_pool
NEWS news_pool[NEWS_SIZE]; int npi;
vector<NEWS*> user_pool[USER_SIZE]; int upi; //Stores NEWS announced to user
vector<int> channel_pool[CHANNEL_SIZE]; int cpi; //Stores registered uID for each channel

void init(int N, int K)
{
	news_queue = {};
	user_info.clear();
	news_info.clear();
	channel_info.clear();

	upi = npi = cpi = 0;
}


void updateNews(int mTime) //send a notification first if there is a news sent to the user at the mTime
{
	while (!news_queue.empty())
	{
		auto cur = news_queue.top();
		if (cur->release_time > mTime) //If release_time is later than mTime, nothing happens
			return;
		news_queue.pop();

		if (cur->canceled) //If its canceled NEWS
			continue;

		for (int i = 0; i < channel_pool[cur->channel_id].size(); i++) //send NEWS to the registered users
			user_pool[channel_pool[cur->channel_id][i]].push_back(cur);
	}
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	updateNews(mTime);

	int now_uId; //not user's ID, but idx idx for user_pool
	if (user_info.find(mUID) == user_info.end()) //If mUID is not in the hash(=New User)
	{
		now_uId = user_info[mUID] = upi++; //Add to user_info
		user_pool[now_uId].clear();
	}
	else
		now_uId = user_info[mUID];

	for (int i = 0; i < mNum; i++) //Add uID to mChannelIDs[]
	{
		int now_cId; //Not just ChannelID, but idx for channel_info
		if (channel_info.find(mChannelIDs[i]) == channel_info.end()) //If the channel is not in the hash(=New channel)
		{
			now_cId = channel_info[mChannelIDs[i]] = cpi++; //Add to channel_info
			channel_pool[now_cId].clear();
		}
		else
			now_cId = channel_info[mChannelIDs[i]];
												
		channel_pool[now_cId].push_back(now_uId); //save idx for user_pool in the channel_pool
	}
}

// int release_time;
// int news_id;
// int channel_id;
// bool canceled;
int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	news_pool[npi] = {mTime+mDelay, mNewsID, channel_info[mChannelID], false};
	//Since PQ stores address of the NEWS in news_pool, 
	//when value in the news_pool is changed the value in the PQ is also changed
	news_queue.push(&news_pool[npi]); 
	news_info[mNewsID] = npi++;

	return channel_pool[channel_info[mChannelID]].size();

}

void cancelNews(int mTime, int mNewsID)
{
	news_pool[news_info[mNewsID]].canceled = true;
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	updateNews(mTime);

	int user_idx = user_info[mUID];
	int ans = user_pool[user_idx].size();
	int cnt = 0;

	//News is stored in chronological order
	//It means the latest NEWS is stored at the very back
	//Check from the back
	for(int i=user_pool[user_idx].size()-1; i>= 0; --i){
		if(user_pool[user_idx][i]->canceled){
			ans--;
		}
		else if(cnt < 3){
			mRetIDs[cnt++] = user_pool[user_idx][i]->news_id;
		}
	}

	//After the function is called, 
	//all news notifications received by the mUID user are deleted, 
	//and the number of notifications becomes 0.
	user_pool[user_idx].clear();

	return ans;

}
