/****************************************************************************************
 *
 * file name : test
 * auther    : Wxl
 * date      : 2025/3/25
 * note      : none
 *
 * CopyRight (c) : 2025             all right reasever
 *
 ****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 为了顺序表更好的可移植性
typedef int DateType;

typedef struct SequenceList
{
    DateType *addr;
    unsigned int size;
    int last;
} SequenceList_t;

// 创建顺序表
SequenceList_t *SeqeList_Create(unsigned int size)
{
    // 为管理顺序表的结构体地址申请堆内存
    SequenceList_t *Manage = (SequenceList_t *)calloc(1, sizeof(SequenceList_t));
    // 错误处理
    if (Manage == NULL)
    {
        perror("malloc for Manage is failed");
        exit(-1);
    }
    // 为顺序表申请堆内存
    Manage->addr = (DateType *)calloc(size, sizeof(DateType));
    // 错误处理
    if ((Manage->addr) == NULL)
    {
        free(Manage);
        perror("colloc for addr is faile");
        exit(-1);
    }
    // 为管理顺序表结构体赋值
    Manage->size = size;
    Manage->last = -1;
    return Manage;
}

// 判断顺序表是否已满（存在和是否已满）
bool SeqeList_IsFull(SequenceList_t *Manage)
{
    // 判读顺序表是否存在
    if (Manage->addr == NULL)
    {
        printf("This SeqeList  does not exist\n");
        return true;
    }
    // 判断顺序表是否已满
    if (Manage->last == (Manage->size - 1))
    {
        printf("This SeqeList is full\n");
        return true;
    }
    return false;
}

// 顺序表插入元素(尾部)
bool SeqeList_TailInsert(SequenceList_t *Manage, DateType Date)
{
    // 判读顺序表是否合法
    if (SeqeList_IsFull(Manage))
    {
        return false;
    }
    // 将新元素添加到顺序表尾部(将last加一位后作为下标)
    Manage->addr[++Manage->last] = Date;
    // 返回完成标志
    return true;
}

// 顺序表插入元素（头部）
bool SeqeList_HeadInsert(SequenceList_t *Manage, DateType Date)
{
    // 判读顺序表是否合法
    if (SeqeList_IsFull(Manage))
    {
        return false;
    }
    // 将元素完后挪一位
    for (int i = Manage->last; i >= 0; i--)
    {
        Manage->addr[i + 1] = Manage->addr[i];
    }
    // 插入元素（头部）并且更新管理结构体中的末尾下表
    Manage->addr[0] = Date;
    Manage->last++;
}

// 判断顺序表是否为空（存在和是否为空）
bool SeqeList_IsEmpty(SequenceList_t *Manage)
{
    // 判读顺序表是否存在
    if (Manage->addr == NULL)
    {
        printf("This SeqeList  does not exist\n");
        return true;
    }
    // 判断顺序表是否为空
    if (Manage->last == -1)
    {
        printf("This SeqeList is Empty\n");
        return true;
    }
    return false;
}

// 删除顺序表中元素
bool SeqeList_Del(SequenceList_t *Manage, DateType DateDel)
{
    // 判断合法
    if (SeqeList_IsEmpty(Manage))
    {
        return false;
    }
    // 判断删除元素是否存在
    int flag = -1;
    for (int i = 0; i <= Manage->last; i++)
    {
        if (Manage->addr[i] == DateDel)
        {
            flag = i;
            break;
        }
    }
    // 如果存在则删除，并且整理下标，不存在直接返回
    // 存在
    if (flag != -1)
    {
        for (int i = flag; i < Manage->last; i++)
        {
            Manage->addr[i] = Manage->addr[i + 1];
        }
        Manage->last--;
        return true;
    }
    else
    {
        printf("DateDel is Doesn't exist\n");
        return false;
    }
}

// 已知一个顺序表L，其中的元素递增有序排列，设计一个算法，插入一个元素x(x为int型)后保持该顺序表仍然递增有序排列(假设插入操作总能成功)。
//  顺序插入顺序表元素，保证插入后依然排列有序，由低到高
bool SeqeList_SeqeInsert(SequenceList_t *Manage, DateType Date)
{
    // 找到应该插入的位置
    int flag = Manage->last + 1;
    for (int i = 0; i <= Manage->last; i++)
    {
        if (Manage->addr[i] > Date)
        {
            flag = i;
            break;
        }
    }
    // 将后面的元素往后挪一位
    for (int j = Manage->last; j >= flag; j--)
    {
        Manage->addr[j + 1] = Manage->addr[j];
    }
    // 插入并更新顺序表最后元素下标
    Manage->addr[flag] = Date;
    Manage->last++;
    return true;
}

// 遍历顺序表
void seqeList_Print(SequenceList_t *Manage)
{
    for (int i = 0; i <= Manage->last; i++)
    {
        printf("Element[%d] = %d\n", i, Manage->addr[i]);
    }
}

int main()
{
    SequenceList_t *manage = NULL;
    // 1.创建顺序表
    manage = SeqeList_Create(10);
    // 2.插入元素（尾插）
    for (int i = 0; i < 5; i++)
    {
        SeqeList_TailInsert(manage, 2 * i);
    }
    // 3.遍历顺序表
    printf("add result:\n");
    seqeList_Print(manage);
    // 4.顺序插入顺序表
    SeqeList_SeqeInsert(manage, 5);
    // 5.遍历顺序表
    printf("SeqeInsert result:\n");
    seqeList_Print(manage);
    // 6.头部插入
    SeqeList_HeadInsert(manage, 1);
    // 7.遍历顺序表
    printf("HeadInsert result:\n");
    seqeList_Print(manage);
    // 8.删除5
    SeqeList_Del(manage, 90);
    SeqeList_Del(manage, 1);
    SeqeList_Del(manage, 8);
    SeqeList_Del(manage, 30);
    // 9.遍历
    printf("SeqeList_Del result:\n");
    seqeList_Print(manage);

    return 0;
}