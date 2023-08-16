#include <unordered_map>
#include <vector>
#include <queue>
#define USER_SIZE 501
#define CHANNEL_SIZE 501
#define NEWS_SIZE 30001

using namespace std;

typedef struct NEWS
{
	int release_time;
	int news_id;
	int channel_id;
	bool canceled;

    bool operator>(const NEWS& other) const{
        if(release_time == other.release_time){
            return news_id > other.news_id;
        }
        return release_time > other.release_time;
    }
}NEWS;

unordered_map<int, int> user_info; //UID를 user_pool에서 사용하는 idx로 변한하기 위한 해쉬
unordered_map<int, int> news_info;
unordered_map<int, int> channel_info;
priority_queue<NEWS*, vector<NEWS*>, NEWS> news_queue;

NEWS news_pool[NEWS_SIZE]; int npi;
vector<NEWS*> user_pool[USER_SIZE]; int upi;
vector<int> channel_pool[CHANNEL_SIZE]; int cpi; //각 채널별 구독중인 uID를 저장

void init(int N, int K)
{
	news_queue = {};
	user_info.clear();
	news_info.clear();
	channel_info.clear();

	upi = npi = cpi = 0;
}

void updateNews(int mTime) //mTime 시각에 유저에게 보내지는 뉴스 알림이 있는 경우 먼저 알림을 보내기 위한 함수
{
	while (!news_queue.empty())
	{
		auto cur = news_queue.top();
		if (cur->release_time > mTime) //만약 현재 시간보다 release_time이 크다면 업데이트 x
			return;
		news_queue.pop();

		if (now_news->canceled) //만약 취소된 뉴스라면
			continue;

		for (int i = 0; i < channel_pool[now_news->channel_id].size(); i++) //해당 채널을 구독중인 유저들에게 뉴스 알람을 보냄
			user_pool[channel_pool[now_news->channel_id][i]].push_back(now_news);
	}
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	updateNews(mTime);

	int now_uId; //원래 UID가 아니라 user_pool에서 사용하는 idx
	if (user_info.find(mUID) == user_info.end()) //해당 유저가 해쉬에 없다면(처음 등장한 유저라면)
	{
		now_uId = user_info[mUID] = upi++; //user_info에 등록
		user_pool[now_uId].clear();
	}
	else
		now_uId = user_info[mUID];

	for (int i = 0; i < mNum; i++) //유저가 등록하는 모든 채널에 유저를 추가
	{
		int now_cId; //원래 ChannelID가 아니라 channel_info에서 사용하는 Idx
		if (channel_info.find(mChannelIDs[i]) == channel_info.end()) //해당 채널이 해쉬에 없다면(처음 등장한 채널이라면)
		{
			now_cId = channel_info[mChannelIDs[i]] = cpi++; //channel_info에 등록
			channel_pool[now_cId].clear();
		}
		else
			now_cId = channel_info[mChannelIDs[i]];

		channel_pool[now_cId].push_back(now_uId); //channel_pool에, 해당 채널에 맞는 idx에 user_pool에서 사용하는 idx 저장
	}
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	// int now_cId = channel_info[mChannelID]; //
	// int now_nId = news_info[mNewsID] = npi++;
	// news_pool[now_nId] = { mTime + mDelay, mNewsID, now_cId, false };

	// news_queue.push(&news_pool[now_nId]);

	// return channel_pool[now_cId].size();
}

void cancelNews(int mTime, int mNewsID)
{
	// news_pool[news_info[mNewsID]].canceled = true;
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	// updateNews(mTime);

	// int now_uId = user_info[mUID];
	// int ret = user_pool[now_uId].size();
	// int cnt = 0;
	// for (int i = user_pool[now_uId].size() - 1; i >= 0; i--)
	// {
	// 	if (user_pool[now_uId][i]->canceled)
	// 		ret--;
	// 	else if (cnt < 3)
	// 		mRetIDs[cnt++] = user_pool[now_uId][i]->news_id;
	// }
	// user_pool[now_uId].clear();

	// return ret;
}