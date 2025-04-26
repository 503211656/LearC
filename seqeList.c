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

// Ϊ��˳�����õĿ���ֲ��
typedef int DateType;

typedef struct SequenceList
{
    DateType *addr;
    unsigned int size;
    int last;
} SequenceList_t;

// ����˳���
SequenceList_t *SeqeList_Create(unsigned int size)
{
    // Ϊ����˳���Ľṹ���ַ������ڴ�
    SequenceList_t *Manage = (SequenceList_t *)calloc(1, sizeof(SequenceList_t));
    // ������
    if (Manage == NULL)
    {
        perror("malloc for Manage is failed");
        exit(-1);
    }
    // Ϊ˳���������ڴ�
    Manage->addr = (DateType *)calloc(size, sizeof(DateType));
    // ������
    if ((Manage->addr) == NULL)
    {
        free(Manage);
        perror("colloc for addr is faile");
        exit(-1);
    }
    // Ϊ����˳���ṹ�帳ֵ
    Manage->size = size;
    Manage->last = -1;
    return Manage;
}

// �ж�˳����Ƿ����������ں��Ƿ�������
bool SeqeList_IsFull(SequenceList_t *Manage)
{
    // �ж�˳����Ƿ����
    if (Manage->addr == NULL)
    {
        printf("This SeqeList  does not exist\n");
        return true;
    }
    // �ж�˳����Ƿ�����
    if (Manage->last == (Manage->size - 1))
    {
        printf("This SeqeList is full\n");
        return true;
    }
    return false;
}

// ˳������Ԫ��(β��)
bool SeqeList_TailInsert(SequenceList_t *Manage, DateType Date)
{
    // �ж�˳����Ƿ�Ϸ�
    if (SeqeList_IsFull(Manage))
    {
        return false;
    }
    // ����Ԫ����ӵ�˳���β��(��last��һλ����Ϊ�±�)
    Manage->addr[++Manage->last] = Date;
    // ������ɱ�־
    return true;
}

// ˳������Ԫ�أ�ͷ����
bool SeqeList_HeadInsert(SequenceList_t *Manage, DateType Date)
{
    // �ж�˳����Ƿ�Ϸ�
    if (SeqeList_IsFull(Manage))
    {
        return false;
    }
    // ��Ԫ�����Ųһλ
    for (int i = Manage->last; i >= 0; i--)
    {
        Manage->addr[i + 1] = Manage->addr[i];
    }
    // ����Ԫ�أ�ͷ�������Ҹ��¹���ṹ���е�ĩβ�±�
    Manage->addr[0] = Date;
    Manage->last++;
}

// �ж�˳����Ƿ�Ϊ�գ����ں��Ƿ�Ϊ�գ�
bool SeqeList_IsEmpty(SequenceList_t *Manage)
{
    // �ж�˳����Ƿ����
    if (Manage->addr == NULL)
    {
        printf("This SeqeList  does not exist\n");
        return true;
    }
    // �ж�˳����Ƿ�Ϊ��
    if (Manage->last == -1)
    {
        printf("This SeqeList is Empty\n");
        return true;
    }
    return false;
}

// ɾ��˳�����Ԫ��
bool SeqeList_Del(SequenceList_t *Manage, DateType DateDel)
{
    // �жϺϷ�
    if (SeqeList_IsEmpty(Manage))
    {
        return false;
    }
    // �ж�ɾ��Ԫ���Ƿ����
    int flag = -1;
    for (int i = 0; i <= Manage->last; i++)
    {
        if (Manage->addr[i] == DateDel)
        {
            flag = i;
            break;
        }
    }
    // ���������ɾ�������������±꣬������ֱ�ӷ���
    // ����
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

// ��֪һ��˳���L�����е�Ԫ�ص����������У����һ���㷨������һ��Ԫ��x(xΪint��)�󱣳ָ�˳�����Ȼ������������(�������������ܳɹ�)��
//  ˳�����˳���Ԫ�أ���֤�������Ȼ���������ɵ͵���
bool SeqeList_SeqeInsert(SequenceList_t *Manage, DateType Date)
{
    // �ҵ�Ӧ�ò����λ��
    int flag = Manage->last + 1;
    for (int i = 0; i <= Manage->last; i++)
    {
        if (Manage->addr[i] > Date)
        {
            flag = i;
            break;
        }
    }
    // �������Ԫ������Ųһλ
    for (int j = Manage->last; j >= flag; j--)
    {
        Manage->addr[j + 1] = Manage->addr[j];
    }
    // ���벢����˳������Ԫ���±�
    Manage->addr[flag] = Date;
    Manage->last++;
    return true;
}

// ����˳���
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
    // 1.����˳���
    manage = SeqeList_Create(10);
    // 2.����Ԫ�أ�β�壩
    for (int i = 0; i < 5; i++)
    {
        SeqeList_TailInsert(manage, 2 * i);
    }
    // 3.����˳���
    printf("add result:\n");
    seqeList_Print(manage);
    // 4.˳�����˳���
    SeqeList_SeqeInsert(manage, 5);
    // 5.����˳���
    printf("SeqeInsert result:\n");
    seqeList_Print(manage);
    // 6.ͷ������
    SeqeList_HeadInsert(manage, 1);
    // 7.����˳���
    printf("HeadInsert result:\n");
    seqeList_Print(manage);
    // 8.ɾ��5
    SeqeList_Del(manage, 90);
    SeqeList_Del(manage, 1);
    SeqeList_Del(manage, 8);
    SeqeList_Del(manage, 30);
    // 9.����
    printf("SeqeList_Del result:\n");
    seqeList_Print(manage);

    return 0;
}