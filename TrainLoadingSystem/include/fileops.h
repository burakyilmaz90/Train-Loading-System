#ifndef FILEOPS_H

#define FILEOPS_H

#include "train.h"

void save_train_file(Train* train , char *filename);
void load_train_fromfile(Train* train,char* filename);
#endif