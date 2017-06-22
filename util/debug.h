//
// Created by wxy on 17.6.22.
//

#ifndef HIHO_PROBLEMS_DEBUG_H
#define HIHO_PROBLEMS_DEBUG_H

#define _DEBUG
#ifdef _DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#endif //HIHO_PROBLEMS_DEBUG_H
