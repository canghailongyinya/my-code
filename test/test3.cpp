#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val):val(val),left(nullptr),right(nullptr){}
};
TreeNode* pre_in_topost(TreeNode *root,int pre_s_l,int pre_s_r,int in_s_l,int in_s_r,vector<int> pre_s,vector<int> in_s)
{
    if (pre_s_r - pre_s_l == 0) return nullptr;
    root = new TreeNode(pre_s[pre_s_l]);
    int i = in_s_l;
    while (in_s[i]!=pre_s[pre_s_l]) i++;
    // string in_s1 = in_s.substr(0,i);
    // string in_s2 = in_s.substr(i+1,in_s.size()-i-1);
    // string pre_s1 = pre_s.substr(1,in_s1.size());
    // string pre_s2 = pre_s.substr(1+in_s1.size(),in_s2.size());
    // root->left = pre_in_topost(root->left,pre_s1,in_s1);
    // root->right = pre_in_topost(root->right,pre_s2,in_s2);
    int in_s1_l = in_s_l,in_s1_r = i,in_s2_l = i + 1,in_s2_r = in_s_r;
    int pre_s1_l = pre_s_l+1,pre_s1_r = pre_s1_l+i-in_s_l;
    int pre_s2_l = pre_s1_r,pre_s2_r = pre_s_r;
    root->left = pre_in_topost(root->left,pre_s1_l,pre_s1_r,in_s1_l,in_s1_r,pre_s,in_s);
    root->right = pre_in_topost(root->right,pre_s2_l,pre_s2_r,in_s2_l,in_s2_r,pre_s,in_s);
    return root;
}
void post_order(TreeNode *root)
{
    if (root == nullptr) return;
    post_order(root->left);
    post_order(root->right);
    cout<<root->val<<" ";
}
void DeleteTree(TreeNode *root)
{
    if (root == nullptr) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}
int main()
{
    int n;
    cin>>n;
    vector<int> pre_s(n),in_s(n);
    for (int i = 0;i < n;i++) {
        cin>>pre_s[i];
    }
    for (int i = 0;i < n;i++) {
        cin>>in_s[i];
    }
    TreeNode *root = nullptr;
    root = pre_in_topost(root,0,pre_s.size(),0,in_s.size(),pre_s,in_s);
    post_order(root);
    DeleteTree(root);
    return 0;
}