#include <iostream>
#include <vector>

using namespace std;


int noVideos;
int noEndpoints;
int noRequestDescriptions;
int noCaches;
int cacheSize;

vector<int> videoSizes;
// [datacenter latency][no cache servers][cache server no][cache server latency]
vector< vector<int> > endpoints;
// [videoID][endpointID][no Requests]
vector< vector<int> > requests;

vector<int> videoRequests;

vector< vector<int> > cacheServers;

void getInput()
{
    cin >> noVideos;
    cin >> noEndpoints;
    cin >> noRequestDescriptions;
    cin >> noCaches;
    cin >> cacheSize;

    int temp;
    for(int i = 0; i < noVideos; ++i) {
        cin >> temp;
        videoSizes.push_back(temp);
    }
    // get in endpoints
    for(int i = 0; i < noEndpoints; ++i) {
        vector<int> curEndpoint;
        int temp;
        cin >> temp;    // datacenter latency

        curEndpoint.push_back(temp);

        cin >> temp;    // no of cache servers
        curEndpoint.push_back(temp);
        
        for(int i = 0; i < curEndpoint[1]; ++i) {   // cache server info
            cin >> temp;    // cache server no.
            curEndpoint.push_back(temp);

            cin >> temp;    // latency to current cache server
            curEndpoint.push_back(temp);
        }
        endpoints.push_back(curEndpoint);
   }

   // get in requests
   for(int i = 0; i < noRequestDescriptions; ++i) {
       vector<int> tempReqs;

       int temp;
       cin >> temp;
       tempReqs.push_back(temp);
       cin >> temp;
       tempReqs.push_back(temp);
       cin >> temp;
       tempReqs.push_back(temp);

       requests.push_back(tempReqs);
   }

}

void testGetInput()
{
    cout << noVideos << endl;
    cout << noEndpoints << endl;
    cout << noRequestDescriptions << endl;
    cout << noCaches << endl;
    cout << cacheSize << endl;

    for(int i = 0; i < videoSizes.size(); ++i)
        cout << videoSizes[i] << " ";
    cout << endl;

    vector<int> tempEnd = endpoints[3];

    int a = tempEnd[1];
    cout << a << endl;
    for(int i = 2; i < 2*a+2; i+=2) {
        cout << tempEnd[i] << " ";
        cout << tempEnd[i+1] << endl;
    }
    
    cout << "REQUESTS" << endl;
    for(int i = 0; i < requests.size(); ++i) {
        cout << requests[i][0] << " ";
        cout << requests[i][1] << " ";
        cout << requests[i][2] << " ";

        cout << endl;
    }
}

void john()
{
    for(int i = 0; i < videoRequests.size(); ++i) {
        if(videoRequests[i] > 0) {


            int mostRequested = -1;
            int endpointMost = -1;

            for(int j = 0; j < requests.size(); ++j) {
                if(requests[j][0] == i) {// request for this video
                    if(requests[j][2] > mostRequested ) {
                        mostRequested = requests[j][2];
                        endpointMost = requests[j][1];
                    }
                    }
                }
            cout << "Endpoint: " << endpointMost << " requests " << mostRequested << " for video[" << i << "]" << endl;
        }
    }
}

int sumVideoSize()  // in MB
{
    int sum = 0;
    for(int i = 0; i < videoSizes.size(); ++i)
        sum += videoSizes[i];
    return sum;
}

int sumRequestedVideoSize()
{
    int sum = 0;
    for(int i = 0; i < videoSizes.size(); ++i)
        if(videoRequests[i] > 0)
            sum += videoSizes[i];
    return sum;
}
void fillVideoRequests()
{
    for(int i = 0; i < noVideos; ++i) {
        videoRequests.push_back(0);
    }

    for(int i = 0; i < requests.size(); ++i) {
        videoRequests[ requests[i][0] ] += requests[i][2];
    }
}

int addToCache(int cacheNumber, int videoNum)
{
    int totCacheSize = 0;
    cacheServers[cacheNumber].push_back(videoNum);

    for(int i = 0; i < cacheServers[cacheNumber].size(); ++i) {
        totCacheSize += cacheServers[cacheNumber][i];
    }

    if(totCacheSize > cacheSize)
        return 0;
    else
        return 1
}
int main()
{
    getInput();
    testGetInput();
    cout << sumVideoSize() << endl;
    fillVideoRequests();

    for(int i = 0; i < videoRequests.size(); ++i) {
        
        if(videoRequests[i] > 0)
             cout << "Video[" << i << "] requests: " << videoRequests[i] << " size per video " << videoSizes[i] << " total requests data " << videoSizes[i]*videoRequests[i] << endl;
    }

    cout << sumRequestedVideoSize() << endl;
    john();
}