//
//  utility.hpp
//  MRPMMainServer
//
//  Created by Naoya Sakabe on 2016/10/30.
//
//
#pragma once
#include <functional>

class SparseExecutor{
public:
    SparseExecutor(int _mod,
                   std::function<void()> _fn
                   );
    void touch();
private:
    std::function<void()> fn;
    int mod;
    int count;
    SparseExecutor();
};
