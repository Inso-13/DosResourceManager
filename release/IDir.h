#if !defined(__IDIR_H)
#define __IDIR_H

void Icd(char far*); // setdisk & cd
IFileNode far* IAddFileNode(char far* path);// enlarge the filetree
void IDetree(IFileNode far* root); // delete the filetree
IBool IEntree(IFileNode far* root); // build the filetree
void IUpdateFileNode(IFileNode far* curNode); // update a node(to del or to insert a new filenode)

#endif