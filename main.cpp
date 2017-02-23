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

int addToCache(int cacheNumber, int videoNum)
{
    int totCacheSize = 0;
    cacheServers[cacheNumber].push_back(videoNum);

    for(int i = 0; i < cacheServers[cacheNumber].size(); ++i) {
        totCacheSize += cacheServers[cacheNumber][i];
    }

    if(totCacheSize > cacheSize) {
        cacheServers[cacheNumber].pop_back();
        return 0;
    }
    else {
        return 1;
    }
}

int isCacheFull(int cacheNumber, int videoNum)
{
    int totCacheSize = 0;

    for(int i = 0; i < cacheServers[cacheNumber].size(); ++i) {
        totCacheSize += videoSizes[ cacheServers[cacheNumber][i] ];
    }

    //cout << "totot " << totCacheSize << endl;
    if(totCacheSize + videoSizes[videoNum] + 1>= cacheSize) {
        return 1;
    } else {
        return 0;
    }

}

int quickestCacheAvailable(int endpointNo)
{

}
int quickestCache(int endpointNo, int videoNo)   // returns cacheNo or -1 if no cache
{
    int cacheNo = -1;
    int lowestLat;
    if(endpoints[endpointNo].size() >= 4) {
        lowestLat = endpoints[endpointNo][3];
        cacheNo = 0;
    } else {
        return -1;
    }

    for(int i = 3; i < endpoints[endpointNo].size(); i += 2) {
        int tcn = endpoints[endpointNo][i-1];
        if(endpoints[endpointNo][i] < lowestLat && !isCacheFull(tcn, videoNo ) ) {
            lowestLat = endpoints[endpointNo][i];
            cacheNo = endpoints[endpointNo][i-1];
        }
    }

    if(isCacheFull(cacheNo, videoNo)) {
        return -1;
    }
    return cacheNo;
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
            //cout << "Endpoint: " << endpointMost << " requests " << mostRequested << " for video[" << i << "]" << endl;
            int quickC;
            quickC = quickestCache(endpointMost, i);
            if(quickC > 0) {
                addToCache(quickC, i);
            } else {

            }

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

void cacheInitialise()
{
    vector<int> t;

    for(int i = 0; i < noCaches; ++i) {
        cacheServers.push_back(t);
    }
}




int main()
{
    getInput();
    cacheInitialise();

    //testGetInput();
    //cout << sumVideoSize() << endl;
    fillVideoRequests();
/*
    for(int i = 0; i < videoRequests.size(); ++i) {
        
        if(videoRequests[i] > 0)
             cout << "Video[" << i << "] requests: " << videoRequests[i] << " size per video " << videoSizes[i] << " total requests data " << videoSizes[i]*videoRequests[i] << endl;
    }

    cout << sumRequestedVideoSize() << endl; */
    john();


    //cacheServers[1].pop_back();

    int noUsed = 0;
    for(int i = 0; i < cacheServers.size(); ++i) {
        if(cacheServers[i].size() > 0)
            noUsed++;
    }

    cout << noUsed << endl;
    for(int i = 0; i < cacheServers.size(); ++i) {
        if(cacheServers[i].size() > 0) {
            cout << i << " "; // cache no

            for(int j = 0; j < cacheServers[i].size(); ++j) {
                cout << cacheServers[i][j] << " ";
            }
        
        cout << endl;
        }
    }

    //cout << isCacheFull(1, 31) << endl;
}