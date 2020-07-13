#if !defined(__IDIR_H)
#define __IDIR_H

IFileNode far* IDiskInit(void);
IBool IisFolder(IFileNode far* node);
void Icd(char far*); // setdisk & cd
IBool IMatch(char* src,char* pattern);
IBool IGetPath(IFileNode far* node,char* temp);
IBool IAddFileNode(IFileNode far *parent,char* name);
IBool IDelFileNode(IFileNode far *parent,char* name);
IFileNode far* IGetFileNodeList(char far* path);// enlarge the filetree
void IDetree(IFileNode far* root); // delete the filetree
IBool IEntree(IFileNode far* root); // build the filetree
IFileNode far* IFindNodeByPath(char far* path,IFileNode far* root);
IFileNode far* IFindNodeByName(char far* name,IFileNode far* root);
IBool Icopy(IFileNode far* inFile,IFileNode far* outParent);
IBool Irmf(IFileNode far* fileNode);
IBool Inew(IFileNode far* pathNode,IFileNode far* fileName);
void Imkdir(IFileNode far* pathNode,IFileNode far* folderName);
void Imvdir(IFileNode far* oldChild,IFileNode far* newParent);
IBool Irmdir(IFileNode far* node);
IBool Irename(IFileNode far* oldName,IFileNode far* newName);
void ICopyAll(IFileNode far* oldChildChild,IFileNode far* newChild);
void IDelAll(IFileNode far* oldChildChild);
void Icpr(IFileNode far* oldChild,IFileNode far* newParent);
void Irmr(IFileNode far* oldChild);
void Icplr(IFileNode far* oldParent,IFileNode far* newParent);
void Irmlr(IFileNode far* oldParent,IFileNode far* rootR);
void IPeek(IFileNode far* oldParent);
IFileNode far* ISearch(IFileNode far* node,IFileNode far* name);

#endif