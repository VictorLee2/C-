/************************************************
    这是一个通讯录小程序
    可实现的操作：
    1.菜单
    2.打印（一次打印多少个人的数据？）
    3.查找（按哪个特性查找？）
    4.添加
    5.修改
    6.删除
    7.清空通讯录
    8.对通讯录内的数据进行排序显示
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30

int list_length = 0;
//通讯录要包含的数据
typedef struct AddressNode
{
    char name[MAXSIZE];
    char sex[MAXSIZE];
    char work[MAXSIZE];
    char phone[MAXSIZE];
    char address[MAXSIZE];
    struct AddressNode *next;
}AddNode, *AddBook;

//通讯录初始化
void InitAdd(AddBook *head)
{
    AddBook temp, target;
    char c = 'y';
    target = NULL;

    while(c == 'y')
    {
        fflush(stdin);

        if(*head == NULL)
        {
            *head = (AddNode *)malloc(sizeof(AddNode));

            if(!(*head))
            {
                printf("分配动态内存空间失败！\n");
                exit(1);
            }

            (*head)->next = NULL;
            printf("请输入第%d位联系人的信息:\n", list_length+1);
            printf("请输入该联系人的姓名:");
            gets((*head)->name);
            printf("请输入该联系人的性别:");
            gets((*head)->sex);
            printf("请输入该联系人的职业:");
            gets((*head)->work);
            printf("请输入该联系人的电话:");
            gets((*head)->phone);
            printf("请输入该联系人的地址:");
            gets((*head)->address);

            list_length++;
            target = *head;
        }
        else
        {
            temp = (AddNode *)malloc(sizeof(AddNode));

            if(!temp)
            {
                printf("分配动态内存空间失败！\n");
                exit(1);
            }

            temp->next = NULL;
            printf("请输入第%d位联系人的信息:\n", list_length+1);
            printf("请输入该联系人的姓名:");
            gets(temp->name);
            printf("请输入该联系人的性别:");
            gets(temp->sex);
            printf("请输入该联系人的职业:");
            gets(temp->work);
            printf("请输入该联系人的电话:");
            gets(temp->phone);
            printf("请输入该联系人的地址:");
            gets(temp->address);

            list_length++;

            target->next = temp;
            target = temp;
        }

        printf("还要继续输入吗?(y/n)\n");
        fflush(stdin);
        scanf("%c", &c);
    }
    return;
}

//输出个人信息
void PrintMan(AddBook target)
{
    printf("%s", target->name);
    printf("        ");
    printf("%s", target->sex);
    printf("        ");
    printf("%s", target->work);
    printf("        ");
    printf("%s", target->phone);
    printf("        ");
    printf("%s", target->address);
    printf("        ");
    printf("\n");
}

//通讯录的打印
void PrintAdd(AddBook head)
{
    AddBook target;
    target = head;
    int i = 1;

    printf("通讯录共有%d位联系人,详细信息如下:\n", list_length);
    printf("序号=======姓名========性别=======职位===========电话================地址\n");
    while(target != NULL)
    {
        printf("%2d", i);
        printf("        ");
        PrintMan(target);
        target = target->next;
        i++;
    }
    return;
}

//通讯录的增加
void InsertAdd(AddBook *head)
{
    AddBook temp, target;
    char c = 'y';

    while(c == 'y')
    {
        temp = (AddNode *)malloc(sizeof(AddNode));

        if(!temp)
        {
            printf("分配动态内存空间失败！\n");
            exit(1);
        }

        temp->next = NULL;
        fflush(stdin);
        printf("请输入添加的联系人的信息:\n");
        printf("请输入该联系人的姓名:");
        gets(temp->name);
        printf("请输入该联系人的性别:");
        gets(temp->sex);
        printf("请输入该联系人的职业:");
        gets(temp->work);
        printf("请输入该联系人的电话:");
        gets(temp->phone);
        printf("请输入该联系人的地址:");
        gets(temp->address);

        if(list_length == 0)
        {
            *head = temp;
            target = *head;
        }
        else
        {
            for(target = *head; target->next != NULL ; target = target->next)
                ;
            target->next = temp;
            target = temp;
        }
        list_length++;

        printf("还要继续添加吗?(y/n)\n");
        fflush(stdin);
        scanf("%c", &c);
    }

    PrintAdd(*head);
    return;
}

//通讯录的删除
void DeleteAdd(AddBook *head)
{
    AddBook pre, target;
    char name[MAXSIZE];
    int flag = 0;

    if(*head == NULL)
    {
        printf("通讯录无数据，不能进行删除操作！\n");
        return;
    }

    fflush(stdin);
    printf("请输入需要删除的姓名:");
    gets(name);
    target = pre = *head;

    while(target != NULL)
    {
        if(strcmp(target->name, name) == 0)
        {
            if(target == *head)
            {
                *head = (*head)->next;
            }
            else
            {
                pre->next = target->next;
            }
            free(target);
            flag = 1;
            break;
        }
        pre = target;
        target = target->next;
    }
    if(flag == 1)
    {
        printf("删除操作成功！\n");
        list_length--;
    }
    else
    {
        printf("不存在此联系人！\n");
    }

    PrintAdd(*head);
    return;
}

//通讯录的修改
void AlterAdd(AddBook *head)
{
    AddBook target;
    char temp[MAXSIZE];
    int i = 1, flag = 0;

    fflush(stdin);
    printf("请输入需要修改的联系人姓名:");
    gets(temp);

    for(target = *head; target != NULL; target = target->next)
    {
        if(strcmp(target->name, temp) == 0)
        {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
    {
        printf("此联系人不存在！\n");
    }
    else
    {
        while(i != 0)
        {
            printf("1.修改姓名  2.修改性别  3.修改职业  4.修改电话  5.修改地址\n");
            printf("请输入数字修改相应的值:");
            scanf("%d", &i);
            fflush(stdin);
            printf("请输入修改的值:");
            gets(temp);

            switch(i)
            {
                case 1:
                    strcpy(target->name, temp);
                    break;
                case 2:
                    strcpy(target->sex, temp);
                    break;
                case 3:
                    strcpy(target->work, temp);
                    break;
                case 4:
                    strcpy(target->phone, temp);
                    break;
                case 5:
                    strcpy(target->address, temp);
                    break;
            }
            printf("是否继续修改？(1/0)\n");
            scanf("%d", &i);
        }
    }

    PrintAdd(*head);
    return;
}

//通讯录的查找
void SearchAdd(AddBook *head)
{
    AddBook target;
    char temp[MAXSIZE];
    int i = 1, flag = 0;

    while(i != 0)
    {
        printf("1.按姓名查找  2.按性别查找  3.按职业查找  4.按电话查找  5.按地址查找\n");
        printf("请输入数字查找相应的值:");
        scanf("%d", &i);
        fflush(stdin);
        printf("请输入查找的值:");
        gets(temp);

        switch(i)
            {
                case 1:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->name, temp) == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("查找的联系人不存在！\n");
                    }
                    else
                    {
                        printf("查找的联系人信息为:\n");
                        PrintMan(target);
                    }
                    break;
                case 2:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->sex, temp) == 0)
                        {
                            printf("查找的联系人信息为:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("查找的联系人不存在！\n");
                    }
                    break;
                case 3:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->work, temp) == 0)
                        {
                            printf("查找的联系人信息为:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("查找的联系人不存在！\n");
                    }
                    break;
                case 4:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->phone, temp) == 0)
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("查找的联系人不存在！\n");
                    }
                    else
                    {
                        printf("查找的联系人信息为:\n");
                        PrintMan(target);
                    }
                    break;
                case 5:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->address, temp) == 0)
                        {
                            printf("查找的联系人信息为:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("查找的联系人不存在！\n");
                    }
                    break;
            }
            printf("是否继续查找？(1/0)\n");
            scanf("%d", &i);
    }
    return;
}

//通讯录的整体删除
void DestroyAdd(AddBook *head)
{
    AddBook temp;

    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        list_length--;
    }

    if(list_length == 0 && *head == NULL)
    {
        printf("删除通讯录成功！\n");
    }
    else
    {
        printf("删除通讯录失败...\n");
    }
    return;
}

//通讯录的排序（姓名）
void SortAdd(AddBook *head)
{
    AddBook p, q, temp;

    for(p = *head; p->next != NULL; p = p->next)
    {
        for(q = p->next; q != NULL; q = q->next)
        {
             if(strcmp(p->name, q->name) > 0)
             {
                 temp = p;
                 p = q;
                 q = temp;
             }
        }
    }

    printf("排序后的通讯录:\n");
    PrintAdd(*head);
    return;
}

//通讯录的保存
void save(AddBook *head)
{
    FILE *fp;
    AddBook target;
    //char name[MAXSIZE];

    if(*head == NULL)
    {
        printf("通讯录为空，无法保存！\n");
        return;
    }

    /*
    fflush(stdin);
    printf("请输入要保存的文件名:");
    gets(name);
    */

    if((fp = fopen("address.txt", "w")) == NULL)
    {
        printf("Can not open the file!\n");
        return;
    }

    target = *head;
    fprintf(fp, "姓名     性别      职位      电话      地址\n");
    while(target != NULL)
    {
        fprintf(fp, "%s     %s      %s      %s      %s\n", target->name, target->sex, target->work, target->phone, target->address);
        target = target->next;
    }
    printf("保存成功！\n");
    fclose(fp);
    return;
}

//通讯录的读取(有问题)
void load(AddBook *head)
{
    FILE *fp;
    AddBook target, temp;
    int i = 0;
    //char name[MAXSIZE];
    target = *head;
    /*
    fflush(stdin);
    printf("请输入要输出的文件名:");
    gets(name);
    */

    if((fp=fopen("address.txt", "r")) == NULL)
    {
        printf("未找到文件！\n");
        return;
    }

    if(feof(fp))
    {
        printf("文件为空！\n");
        return;
    }
    /*
    else
    {
        temp = (AddNode *)malloc(sizeof(AddNode));
        fscanf(fp,"%s%s%s%s%s", &temp->name, &temp->sex, &temp->work, &temp->phone, &temp->address);
        rewind(fp);
    }
   */


    while(!feof(fp))
    {
        temp = (AddNode *)malloc(sizeof(AddNode));
        fscanf(fp,"%s%s%s%s%s", &temp->name, &temp->sex, &temp->work, &temp->phone, &temp->address);
        temp->next = NULL;
        if( i > 0 && fgetc(fp) != EOF)  //第一行数据和最后循环读入的EOF值不能被录入
        {
            if(*head == NULL)
            {
                *head = temp;
                target = *head;
            }
            else
            {
                target->next = temp;
                target = temp;
            }
            list_length++;
        }
        i++;
    }
    free(temp);
    PrintAdd(*head);
    fclose(fp);

    return;
}

int main()
{
    AddBook head = NULL;
    int i = 1;

    printf("*******************欢迎使用小小怪下士通讯录系统！*******************\n");
    printf("*** 1.通讯录初始化    2.添加数据      3.删除数据      4.修改数据 ***\n");
    printf("*** 5.查找数据        6.排序输出      7.整表删除      8.文件保存 ***\n");
    printf("*** 9.文件读取        10.显示数据     0.退出                     ***\n");
    printf("*******************      贡献者：Victor Lee      *******************\n");

    while(0 != i)
    {
        printf("\n请输入数字执行相关操作:\n");
        scanf("%d", &i);

        switch(i)
        {
            case 1:
                InitAdd(&head);
                break;

            case 2:
                InsertAdd(&head);
                break;

            case 3:
                DeleteAdd(&head);
                break;

            case 4:
                AlterAdd(&head);
                break;

            case 5:
                SearchAdd(&head);
                break;

            case 6:
                SortAdd(&head);
                break;

            case 7:
                DestroyAdd(&head);
                break;

            case 8:
                save(&head);
                break;

            case 9:
                load(&head);
                break;

            case 10:
                PrintAdd(head);
                break;

            case 0:
                exit(1);
                break;

            default:
                printf("输入数据有误！\n");
                break;
        }
    }
    return 0;
}
