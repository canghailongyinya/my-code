#include <iostream>
#include <vector>
using namespace std;
//template <typename T>
struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
    TreeNode(char x) : val(x), left(NULL), right(NULL) {}
    TreeNode(char x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
TreeNode* buildTree(string s1,string s2)
{
    if (s1.empty()) return nullptr;
    TreeNode* root=new TreeNode(s1[0]);
    int i;
    for (i = 0;i < s1.size();i++) {
        if (s2[i]==s1[0]) break;
    }
    // int lin_l = in_l;
    // int lin_r = in_l + i;
    // int lpre_l = pre_l + 1;
    // int lpre_r = pre_l + i + 1;
    // int rin_l = lin_r + 1;
    // int rin_r = in_r;
    // int rpre_l = lpre_r;
    // int rpre_r = pre_r;
    // root->left = buildTree(s1,s2,lpre_l,lpre_r,lin_l,lin_r);
    // root->right = buildTree(s1,s2,rpre_l,rpre_r,rin_l,rin_r);
    string ls1 = s1.substr(1,i);
    string ls2 = s2.substr(0,i);
    string rs1 = s1.substr(1+i,s1.size()-i-1);
    string rs2 = s2.substr(1+i,s1.size()-i-1);
    root->left = buildTree(ls1,ls2);
    root->right = buildTree(rs1,rs2);
    return root;
}
void in_order(TreeNode* root,string s = "",bool flag = 0,bool first = 1,bool dic = 0)
{
    string text = "NULL";
    if (root!=nullptr) {
        string t(1,root->val);
        text = t;
    }
    string t = s;
    if (!first) {
        if (!dic) {
            t += flag ? "└─ " : "├─ ";
            s += flag ? "   " : "│  ";
        } else {
            t += !flag ? "└─ " : "├─ ";
            s += !flag ? "   " : "│  ";
        }
    }
    first = 0;
    cout<<t<<text<<endl;
    if (root==nullptr) return;
    if (root->left==nullptr&&root->right==nullptr) return;
    in_order(root->left,s,flag,first,0);
    in_order(root->right,s,flag,first,1);
}
void deleteTree(TreeNode* root)
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main()
{
    string s1,s2;
    cin>>s1>>s2;
    TreeNode* root=buildTree(s1,s2);
    in_order(root);
    deleteTree(root);
    return 0;
}
// ABCDEFGHIJLK
// CDBFEGAJIHLK