/**
 * Copyright(C) 2014. TRULY OPTO-ELECTRONICS LTD. All rights reserved.
 *
 * free_lock_slist.h
 * Original Author : cjpthree@126.com, 2014-7-3.
 *
 * Description
 * ����������������Ӧ���ڵ���������������ͦ�á�
 * ���ڴ����������Ż����ܡ�
 */

#ifndef _FREE_LOCK_SLIST_H_
#define _FREE_LOCK_SLIST_H_

typedef struct free_lock_slist_node {
    struct free_lock_slist_node *next; /* ָ������entry */
} free_lock_slist_node_t;

typedef struct free_lock_slist_head_s {
    struct free_lock_slist_node   *next;    /* ����ָ���һ��entry */
    struct free_lock_slist_node   *ptail;   /* ����ָ�����һ��entry */
} free_lock_slist_head_t;

/**
 * ��ʼ������
 */
#define FREE_LOCK_SLIST_HEAD_INIT(name) \
{ \
    (free_lock_slist_node_t *)&(name), \
    (free_lock_slist_node_t *)&(name) \
}

/**
 * ���岢��ʼ������
 * @name: ����ı�ʶ��
 */
#define FREE_LOCK_SLIST_HEAD(name) \
    free_lock_slist_t (name) = FREE_LOCK_SLIST_INIT(name)

/**
 * ��ʼ������
 * @head: ��Ҫ��ʼ��������
 */
#define INIT_FREE_LOCK_SLIST(head) \
do { \
    (head)->next = (free_lock_slist_node_t *)(head); \
    (head)->ptail = (free_lock_slist_node_t *)(head); \
} while (0)

/**
 * ��ʼ��entry
 * @node: ��Ҫ��ʼ����entry
 */
#define INIT_FREE_LOCK_SLIST_NODE(s_node) \
    ((s_node)->next = (free_lock_slist_node_t *)(s_node))

/**
 * �ж��Ƿ�Ϊ������������ֻ��ͷ���
 * @head: the list to test.
 */
#define free_lock_slist_empty(head) \
    ((head)->next == (free_lock_slist_node_t *)(head))

/**
 * �ж������Ƿ�ֻ��һ��entry
 * @head: the list to test.
 */
#define free_lock_slist_is_singular(head) \
    ((head)->ptail == (head)->next)

/**
 * ��ȡ�������һ��entry
 * @head: the list to test.
 */
#define free_lock_slist_get_last(head) \
    ((head)->ptail)

/**
 * ��ȡ�����һ��entry
 * @head: the list to test.
 */
#define free_lock_slist_get_first(head) \
    ((head)->next)

/**
 * ��entry�������һ���µ�entry
 * @new_entry:  Ҫ�����entry
 * @prev_entry: ǰ���Ǹ�entry
 */
#define __free_lock_slist_add(new_entry, prev_entry) \
do { \
    (new_entry)->next = (prev_entry)->next; \
    (prev_entry)->next = (free_lock_slist_node_t *)(new_entry);  \
} while (0)

/**
 * β�巨������entry
 * @new_entry:  new entry to be added
 * @head:       ͷentry
 */
#define free_lock_slist_add_tail(new_entry, head) \
do { \
    if (free_lock_slist_empty(head)) { \
        (head)->ptail = (free_lock_slist_node_t *)(new_entry);  \
         __free_lock_slist_add((new_entry), (head));  \
    } else if (free_lock_slist_is_singular(head)) { \
        __free_lock_slist_add((new_entry), free_lock_slist_get_last(head));  \
        (head)->ptail = (free_lock_slist_node_t *)(new_entry);  \
    } else { \
        __free_lock_slist_add((new_entry), free_lock_slist_get_last(head));  \
        (head)->ptail = (free_lock_slist_node_t *)(new_entry);  \
    } \
} while (0)

/**
 * ������ɾ��prev_entry�����entry
 * @prev_entry: ��Ҫɾ����entry��ǰ���Ǹ�entry
 */
#define __free_lock_slist_del(prev_entry) \
    ((prev_entry)->next = (prev_entry)->next->next)

/**
 * ɾ������ĵ�һ��entry
 * @head: ����ͷentry
 *
 * ���ܺã��Ƽ�ʹ��
 */
#define free_lock_slist_del_head(head) \
do { \
    if (free_lock_slist_empty(head)) { \
        /* do noting */; \
    } else if (free_lock_slist_is_singular(head)) { \
        (head)->ptail = (free_lock_slist_node_t *)(head); \
        __free_lock_slist_del(head); \
    } else { \
        __free_lock_slist_del(head); \
    } \
} while (0)

/**
 * ��ȡ������entry�Ľṹ��ָ��
 * @entry:   �����ڽṹ���е�entry
 * @type:    Ҫ��ȡ�Ľṹ�������
 * @member:  entry�ڽṹ���еı�ʶ��
 */
#define free_lock_slist_entry(entry, type, member) \
    ((type *)((char *)(entry) - (unsigned long)(&((type *)0)->member)))

#endif      /* _FREE_LOCK_SLIST_H_ */
