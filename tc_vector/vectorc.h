#ifndef VECTORC_H
#define VECTORC_H

#include <string.h>
#include "alias.h"

#define         VECTOR_CAPACITY_DEFAULT             (64)
#define         VECTOR_CAPACITY_MAX                 (128<<8)
#define         VECTOR_CAPACITY_RESIZE_MIN          (128)

#define         ERR_CODE_INVALIDPARA                            (-1)
#define         ERR_CODE_INVALID_VECTOR_POSITION                (-2)
typedef void (*PFUNC_OBJ_DESTRUCT)(void* ptr);




typedef struct tagVector_S
{
    void**                    ppData;         /* vector中存放的对象指针 */                
    unsigned int              uiCount;        /* 当前vector中已经存放的对象个数 */
    unsigned int              uiCapacity;     /* vector的容量 */
    PFUNC_OBJ_DESTRUCT        pfnDestruct;    /* vector中对象的析构方法 */

}Vector_S;


/*
 * vector的构造方法
 */
UINT32    Vct_Construct(Vector_S** ppstVector, PFUNC_OBJ_DESTRUCT pfnElementDestruct);

/*
 * vector的销毁
 */
void Vct_Destruct(Vector_S** ppstVector);

/*
 * vector清空
 */
void Vct_Clear(Vector_S** ppstVector);

/*
 * vector设置容量
 */
UINT32 Vct_SetCapacity(Vector_S* pstVector, unsigned int uiCapacity);

/*
 * vector 添加元素
 */
UINT32 Vct_Pushback(Vector_S* pstVector,  void* pObj);

/*
 * vector 添加元素到vector 的首个空位置
 */
UINT32 Vct_Push(Vector_S* pstVector,  void* pObj);

/*
 * vector 弹出对象
 */
void* Vct_Popback(Vector_S* pstVector);

/*
 * 在vector的index位置替换成新的对象值
 */
UINT32 Vct_SetIndex(Vector_S* pstVector, unsigned int uiIndex, void* pObj);

#endif
