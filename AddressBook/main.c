/************************************************
    ����һ��ͨѶ¼С����
    ��ʵ�ֵĲ�����
    1.�˵�
    2.��ӡ��һ�δ�ӡ���ٸ��˵����ݣ���
    3.���ң����ĸ����Բ��ң���
    4.���
    5.�޸�
    6.ɾ��
    7.���ͨѶ¼
    8.��ͨѶ¼�ڵ����ݽ���������ʾ
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 30

int list_length = 0;
//ͨѶ¼Ҫ����������
typedef struct AddressNode
{
    char name[MAXSIZE];
    char sex[MAXSIZE];
    char work[MAXSIZE];
    char phone[MAXSIZE];
    char address[MAXSIZE];
    struct AddressNode *next;
}AddNode, *AddBook;

//ͨѶ¼��ʼ��
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
                printf("���䶯̬�ڴ�ռ�ʧ�ܣ�\n");
                exit(1);
            }

            (*head)->next = NULL;
            printf("�������%dλ��ϵ�˵���Ϣ:\n", list_length+1);
            printf("���������ϵ�˵�����:");
            gets((*head)->name);
            printf("���������ϵ�˵��Ա�:");
            gets((*head)->sex);
            printf("���������ϵ�˵�ְҵ:");
            gets((*head)->work);
            printf("���������ϵ�˵ĵ绰:");
            gets((*head)->phone);
            printf("���������ϵ�˵ĵ�ַ:");
            gets((*head)->address);

            list_length++;
            target = *head;
        }
        else
        {
            temp = (AddNode *)malloc(sizeof(AddNode));

            if(!temp)
            {
                printf("���䶯̬�ڴ�ռ�ʧ�ܣ�\n");
                exit(1);
            }

            temp->next = NULL;
            printf("�������%dλ��ϵ�˵���Ϣ:\n", list_length+1);
            printf("���������ϵ�˵�����:");
            gets(temp->name);
            printf("���������ϵ�˵��Ա�:");
            gets(temp->sex);
            printf("���������ϵ�˵�ְҵ:");
            gets(temp->work);
            printf("���������ϵ�˵ĵ绰:");
            gets(temp->phone);
            printf("���������ϵ�˵ĵ�ַ:");
            gets(temp->address);

            list_length++;

            target->next = temp;
            target = temp;
        }

        printf("��Ҫ����������?(y/n)\n");
        fflush(stdin);
        scanf("%c", &c);
    }
    return;
}

//���������Ϣ
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

//ͨѶ¼�Ĵ�ӡ
void PrintAdd(AddBook head)
{
    AddBook target;
    target = head;
    int i = 1;

    printf("ͨѶ¼����%dλ��ϵ��,��ϸ��Ϣ����:\n", list_length);
    printf("���=======����========�Ա�=======ְλ===========�绰================��ַ\n");
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

//ͨѶ¼������
void InsertAdd(AddBook *head)
{
    AddBook temp, target;
    char c = 'y';

    while(c == 'y')
    {
        temp = (AddNode *)malloc(sizeof(AddNode));

        if(!temp)
        {
            printf("���䶯̬�ڴ�ռ�ʧ�ܣ�\n");
            exit(1);
        }

        temp->next = NULL;
        fflush(stdin);
        printf("��������ӵ���ϵ�˵���Ϣ:\n");
        printf("���������ϵ�˵�����:");
        gets(temp->name);
        printf("���������ϵ�˵��Ա�:");
        gets(temp->sex);
        printf("���������ϵ�˵�ְҵ:");
        gets(temp->work);
        printf("���������ϵ�˵ĵ绰:");
        gets(temp->phone);
        printf("���������ϵ�˵ĵ�ַ:");
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

        printf("��Ҫ���������?(y/n)\n");
        fflush(stdin);
        scanf("%c", &c);
    }

    PrintAdd(*head);
    return;
}

//ͨѶ¼��ɾ��
void DeleteAdd(AddBook *head)
{
    AddBook pre, target;
    char name[MAXSIZE];
    int flag = 0;

    if(*head == NULL)
    {
        printf("ͨѶ¼�����ݣ����ܽ���ɾ��������\n");
        return;
    }

    fflush(stdin);
    printf("��������Ҫɾ��������:");
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
        printf("ɾ�������ɹ���\n");
        list_length--;
    }
    else
    {
        printf("�����ڴ���ϵ�ˣ�\n");
    }

    PrintAdd(*head);
    return;
}

//ͨѶ¼���޸�
void AlterAdd(AddBook *head)
{
    AddBook target;
    char temp[MAXSIZE];
    int i = 1, flag = 0;

    fflush(stdin);
    printf("��������Ҫ�޸ĵ���ϵ������:");
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
        printf("����ϵ�˲����ڣ�\n");
    }
    else
    {
        while(i != 0)
        {
            printf("1.�޸�����  2.�޸��Ա�  3.�޸�ְҵ  4.�޸ĵ绰  5.�޸ĵ�ַ\n");
            printf("�����������޸���Ӧ��ֵ:");
            scanf("%d", &i);
            fflush(stdin);
            printf("�������޸ĵ�ֵ:");
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
            printf("�Ƿ�����޸ģ�(1/0)\n");
            scanf("%d", &i);
        }
    }

    PrintAdd(*head);
    return;
}

//ͨѶ¼�Ĳ���
void SearchAdd(AddBook *head)
{
    AddBook target;
    char temp[MAXSIZE];
    int i = 1, flag = 0;

    while(i != 0)
    {
        printf("1.����������  2.���Ա����  3.��ְҵ����  4.���绰����  5.����ַ����\n");
        printf("���������ֲ�����Ӧ��ֵ:");
        scanf("%d", &i);
        fflush(stdin);
        printf("��������ҵ�ֵ:");
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
                        printf("���ҵ���ϵ�˲����ڣ�\n");
                    }
                    else
                    {
                        printf("���ҵ���ϵ����ϢΪ:\n");
                        PrintMan(target);
                    }
                    break;
                case 2:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->sex, temp) == 0)
                        {
                            printf("���ҵ���ϵ����ϢΪ:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("���ҵ���ϵ�˲����ڣ�\n");
                    }
                    break;
                case 3:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->work, temp) == 0)
                        {
                            printf("���ҵ���ϵ����ϢΪ:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("���ҵ���ϵ�˲����ڣ�\n");
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
                        printf("���ҵ���ϵ�˲����ڣ�\n");
                    }
                    else
                    {
                        printf("���ҵ���ϵ����ϢΪ:\n");
                        PrintMan(target);
                    }
                    break;
                case 5:
                    for(target = *head; target != NULL; target = target->next)
                    {
                        if(strcmp(target->address, temp) == 0)
                        {
                            printf("���ҵ���ϵ����ϢΪ:\n");
                            PrintMan(target);
                            flag = 1;
                        }
                    }
                    if(flag == 0)
                    {
                        printf("���ҵ���ϵ�˲����ڣ�\n");
                    }
                    break;
            }
            printf("�Ƿ�������ң�(1/0)\n");
            scanf("%d", &i);
    }
    return;
}

//ͨѶ¼������ɾ��
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
        printf("ɾ��ͨѶ¼�ɹ���\n");
    }
    else
    {
        printf("ɾ��ͨѶ¼ʧ��...\n");
    }
    return;
}

//ͨѶ¼������������
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

    printf("������ͨѶ¼:\n");
    PrintAdd(*head);
    return;
}

//ͨѶ¼�ı���
void save(AddBook *head)
{
    FILE *fp;
    AddBook target;
    //char name[MAXSIZE];

    if(*head == NULL)
    {
        printf("ͨѶ¼Ϊ�գ��޷����棡\n");
        return;
    }

    /*
    fflush(stdin);
    printf("������Ҫ������ļ���:");
    gets(name);
    */

    if((fp = fopen("address.txt", "w")) == NULL)
    {
        printf("Can not open the file!\n");
        return;
    }

    target = *head;
    fprintf(fp, "����     �Ա�      ְλ      �绰      ��ַ\n");
    while(target != NULL)
    {
        fprintf(fp, "%s     %s      %s      %s      %s\n", target->name, target->sex, target->work, target->phone, target->address);
        target = target->next;
    }
    printf("����ɹ���\n");
    fclose(fp);
    return;
}

//ͨѶ¼�Ķ�ȡ(������)
void load(AddBook *head)
{
    FILE *fp;
    AddBook target, temp;
    int i = 0;
    //char name[MAXSIZE];
    target = *head;
    /*
    fflush(stdin);
    printf("������Ҫ������ļ���:");
    gets(name);
    */

    if((fp=fopen("address.txt", "r")) == NULL)
    {
        printf("δ�ҵ��ļ���\n");
        return;
    }

    if(feof(fp))
    {
        printf("�ļ�Ϊ�գ�\n");
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
        if( i > 0 && fgetc(fp) != EOF)  //��һ�����ݺ����ѭ�������EOFֵ���ܱ�¼��
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

    printf("*******************��ӭʹ��СС����ʿͨѶ¼ϵͳ��*******************\n");
    printf("*** 1.ͨѶ¼��ʼ��    2.�������      3.ɾ������      4.�޸����� ***\n");
    printf("*** 5.��������        6.�������      7.����ɾ��      8.�ļ����� ***\n");
    printf("*** 9.�ļ���ȡ        10.��ʾ����     0.�˳�                     ***\n");
    printf("*******************      �����ߣ�Victor Lee      *******************\n");

    while(0 != i)
    {
        printf("\n����������ִ����ز���:\n");
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
                printf("������������\n");
                break;
        }
    }
    return 0;
}
