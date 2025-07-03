/*
 * @lc app=leetcode id=160 lang=cpp
 *
 * [160] Intersection of Two Linked Lists
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 双指针,如果第一次遍历公共元素相等,则刚好能找到
        // 第二次遍历,一方走到null后,可得公共元素的差,所以要么一定相遇,要么没有公共元素
        // 即当一个链表走到空时,另一个链表则是走到多出的部分,第第二个链表走到空时,开始"正式"判断元素是否相等
    if(headA || headB)
    {
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while(p1!=p2)
        {
            if(p1 == nullptr)
            {
                p1 = headB;
            }else{
                p1 = p1->next;
            }

            if(p2 == nullptr)
            {
                p2 = headA;
            }else{
                p2 = p2->next;
            }


        }
        
        return p1;
    }
        return nullptr;
    }
};
// @lc code=end

