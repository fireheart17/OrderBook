#include <bits/stdc++.h>
using namespace std;
#define pb push_back

// uniform_int_distribution<int>(l,r)(rng);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    // action,type,side,orderid,quantity,price
    vector<char> action = {'A', 'A', 'A', 'A', 'A', 'X', 'M'}; // more A's in order to increase probability of A message
    vector<char> side = {'A', 'B'};
    vector<string> types = {"limitorder", "fillandkill", "marketorder", "fillorkill", "invalidtype"};
    vector<string> messages;
    int num = 1000;//  number of messages to be generated
    cout << num << endl;
    for (int i = 0; i < num; i++)
    {
        int a = uniform_int_distribution<int>(0, action.size() - 1)(rng);
        int type = uniform_int_distribution<int>(0, types.size() - 1)(rng);
        int sd = uniform_int_distribution<int>(0, side.size() - 1)(rng);
        int id = uniform_int_distribution<int>(-2, 75)(rng);
        int price = uniform_int_distribution<int>(-2, 75)(rng);
        int quantity = uniform_int_distribution<int>(-2, 75)(rng);
        string mes;
        mes.pb(action[a]);
        if (a < action.size() - 2)
        {
            mes.pb(',');
            mes += types[type];
            mes.pb(',');
            mes.pb(side[sd]);
            mes.pb(',');
            mes += to_string(id);
            mes.pb(',');
            mes += to_string(quantity);
            if (type != 2)
            {
                mes.pb(',');
                mes += to_string(price);
            }
        }
        else if (a == 1)
        {
            mes.pb(',');
            mes += to_string(id);
        }
        else
        {
            mes.pb(',');
            mes += to_string(id);
            mes.pb(',');
            mes += to_string(quantity);
            if (uniform_int_distribution<int>(0, 1)(rng)) // may or may not modify the price
            {
                mes.pb(',');
                mes += to_string(price);
            }
        }
        cout << mes << endl;
    }
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    clock_t tStart = clock();
#ifndef ONLINE_JUDGE
    freopen("error.txt", "w", stderr);
#endif
    int tt = 1;
    while (tt--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
// cout<<"Time taken: "<<setprecision(10)<<((double)(clock()-tStart)/CLOCKS_PER_SEC)<<" s"<<endl;
#endif
    return 0;
}
