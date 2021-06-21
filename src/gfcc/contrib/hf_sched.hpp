
#ifndef HF_SCHED_HPP_
#define HF_SCHED_HPP_

#include "hf_tamm_common.hpp"

/******* Ferdous's addition codes*********/
typedef int NODE_T;
typedef int EDGE_T;
typedef double VAL_T;

//load data struct
struct Load
{
    NODE_T loadId;
    NODE_T rank;
    NODE_T s1;
    NODE_T s2;
    VAL_T nTasks;
};

//list of loads as a class
class Loads
{
    public:
        EDGE_T nLoads;
        NODE_T maxS1;
        NODE_T maxS2;
        std::vector<Load> loadList;

        Loads()
        {
            maxS1 = 1;
            maxS2 = 1; 
        }
         
        Loads(EDGE_T nloads)
        {
            maxS1 = 1;
            maxS2 = 1; 
            nLoads = nloads; 
            loadList.reserve(nLoads);
        }
};

bool cmpbyFirst(const std::pair<VAL_T,NODE_T> &T1,const std::pair<VAL_T,NODE_T> &T2)
{

    return T1.first > T2.first;
}

//read load files
//Any header content on the load files needs to be started with 
//% sign. Each line should containt 4 white space seperated values
//The rank, s1, s2, nTasks.
void readLoads(std::string fileName, Loads &L)
{
    std::ifstream fileread(fileName.c_str());
    
    if(fileread.is_open()==false)
    {
        std::cout << "No file named "<<fileName<<std::endl;
        std::exit(1);
    }
    while (fileread.peek() == '%') fileread.ignore(2048, '\n');
    
    EDGE_T nLoads = 0; 
    
    NODE_T rank;
    NODE_T s1;
    NODE_T s2;
    VAL_T nTasks;
    
    while(fileread>>rank>>s1>>s2>>nTasks)    
    {
        if (s1+1 > L.maxS1) L.maxS1 = s1;
        if (s2+1 > L.maxS2) L.maxS2 = s2;

        if(nTasks > 0)
        {
            L.loadList.push_back({nLoads,rank,s1,s2,nTasks}) ;
            nLoads++;
        } 
    }    
    L.nLoads = nLoads;
}

void simpleLoadBal(Loads &L, NODE_T nMachine )
{
    //sort Loads array w.r.t to ntasks
    sort(L.loadList.begin(),L.loadList.end(),[](Load a, Load b)
            {
                return a.nTasks > b.nTasks;
            }
    );
    
    //create a pq with nMachine size.
    std::vector< std::pair<VAL_T,NODE_T> > pq;
    std::vector<VAL_T> cW(nMachine);
    std::vector<NODE_T> bV(nMachine);
    std::vector<NODE_T> cV(nMachine);

    NODE_T b_prime = L.nLoads/nMachine;
    cout<<b_prime<<endl;
    NODE_T remainder = L.nLoads%nMachine;

    for(NODE_T i=0;i<nMachine;i++)
    {
            bV[i] = b_prime;
    }
    //settle the remainder
    for(NODE_T i=0;i<remainder;i++)
    {
        bV[i]++; 
    }
    for(NODE_T i=0;i<nMachine;i++)
    {
        pq.push_back(std::make_pair(0,i)); 
        //L.loadList[i].rank = i;
        cW[i] = 0;
        cV[i] = 0;
    } 
    std::make_heap(pq.begin(),pq.end(),cmpbyFirst);
    
    //scan over the loadList array in high to low and place it in the least load availalble queue.
    for(EDGE_T i=0;i<L.nLoads;i++)
    {
        while(1)
        {
            
            auto top = pq.front();
            NODE_T mId = top.second;
            std::pop_heap(pq.begin(),pq.end(),cmpbyFirst);
            pq.pop_back();
            //cout<<"Top machine, mId: "<<top.second<<" total load: "<<cW[mId]<<endl;
            if(cV[mId] < bV[mId] )
            {
                L.loadList[i].rank =mId;
                cV[mId]++;
                top.first = top.first + L.loadList[i].nTasks;
                cW[mId] = cW[mId] + L.loadList[i].nTasks;
                if(cV[mId] < bV[mId])
                {
                    pq.push_back(top); 
                    std::push_heap(pq.begin(),pq.end(),cmpbyFirst);
                    
                }
                //cout<<"Load "<<i<<": "<<L.loadList[i].nTasks<<" assigned machine "<<mId<<": "<<cW[mId]<<endl;
                break;
            }
        } 
    }

}

void createTaskMap(Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> &taskmap, Loads &L)
{
   for(auto i=0;i<L.nLoads;i++) 
   {
        auto u = L.loadList[i].s1;
        auto v = L.loadList[i].s2;
        taskmap(u,v) = L.loadList[i].rank;
        //std::cout<<u<<" "<<v<<" "<<taskmap(u,v)<<" "<<L.loadList[i].nTasks<<std::endl;
   }

}
#endif
/******end of Ferdous's code*****************/
