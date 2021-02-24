
 #include<iostream>
 #include<vector>
 using namespace std;
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution25 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head==nullptr)
        {
            return nullptr;
        }
        ListNode *pResult = new ListNode(0,head);
        ListNode *pTail = pResult;
        ListNode *pEnd = nullptr;
        ListNode *ptr = pResult;
        while(head!=nullptr)
        {
            for(int i = 0; i < k; ++i)
            {
                pTail = pTail->next;
                if (pTail == nullptr)
                {
                    return pResult->next;
                }
            }
            pEnd = pTail->next;//前k个节点反转的末尾节点
            pTail = ptr->next;//第n次翻转后的开始节点
            ptr->next = pEnd;//翻转后的头节点
            while(head !=pEnd)
            {
                ListNode *r = head->next;
                head->next = ptr->next;
                ptr->next = head;
                head = r;
            }
            ptr = pTail;
        }
        
       return pResult->next;
        
    }
};
class Solution26 {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int>::iterator iter1 = nums.begin();
        while(iter1 != nums.end())
        {
            vector<int>::iterator iter2 = iter1 + 1;
            while(iter2 != nums.end())
            {
                if((*iter1) == (*iter2))
                {
                    ++iter2;
                }
                else
                {
                    break;
                }
                
            }
            nums.erase(++iter1,iter2);
        }
        return nums.size();
    }
};
class Solution27 {
public:
    int removeElement(vector<int>& nums, int val) {
        vector<int>::iterator iter = nums.begin() + 1;
        while(iter != nums.end())
        {
            if(*iter == val)
            {
                nums.erase(iter);
            }
            else
            {
                ++iter;
            }
            
        }
        return nums.size();

    }
};

class Solution28 {
public:
    void GetKMPNext(string str,vector<int>& next)
    {
        int iLen = str.length();
        int i = 0;
        int j = -1;
        next[0] = -1;
        while(i < iLen - 1)
        {
            if(j == -1 || str[i] == str[j])
            {
                i++;
                j++;
                next[i] = j;
            }
            else
            {
                j = next[j];
            }
        }
    }
    int FindStrKMP(string haystack, string needle)
    {
        vector<int> next(needle.length());
        GetKMPNext(needle,next);
        int i = 0;
        int j = 0;
        while(i < haystack.length() && j < needle.length())
        {
            if(j == -1  || haystack[i] == needle[j])
            {
                ++i;
                ++j;
            }
            else
            {
                j = next[j];
            }
            if(j > needle.length() - 1) return i - j;
        }
        return -1;
    }
    int strStr(string haystack, string needle) {
        int iLen1 = haystack.length();
        int iLen2 = needle.length();
        int i,j;
        i = 0;
        j = 0;
        char next[iLen2] = {0};
        while(i < iLen1 && j < iLen2)
        {
            if(haystack[i] == needle[j])
            {
                i++;
                j++;
            }
            else
            {
                i = i - j + 1;
                j = 0;
            }
            
        }
        if (j > iLen2 - 1) return i - j;
        return -1;

    }
};
int main()
{
    Solution28 S28;
    string str1 = "";
    string str2 = "";
    cin>>str1;
    cin>>str2;
    std::cout << S28.strStr(str1,str2)<<std::endl;
    std::cout << S28.FindStrKMP(str1,str2)<<std::endl;
    
    string pause;
    cin>>pause;
    return 0;
}