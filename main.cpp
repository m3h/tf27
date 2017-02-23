#include <iostream>
#include <vector>

using namespace std;


int noVideos;
int noEndpoints;
int noRequestDescriptions;
int noCaches;
int cacheSize;

vector<int> videoSizes;
vector< vector<int> > endpoints;
//vector<int>


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

}

int main()
{
    getInput();
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
    
}