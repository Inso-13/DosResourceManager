#if !defined(__IDIR_H)
#define __IDIR_H

void Icd(char*); // setdisk & cd
IFileNode* IAddFileNode(char* path);// enlarge the filetree
void IDetree(IFileNode* root); // delete the filetree
IBool IEntree(IFileNode* root); // build the filetree
void IUpdateFileNode(IFileNode* curNode); // update a node(to del or to insert a new filenode)

#endif