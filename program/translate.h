#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define zh_tw "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\output\\zh_tw.json"
#define us "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\us.txt"
#define cn "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn.txt"
#define tw "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw.txt"
#define us1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\us1.txt"
#define us2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\us2.txt"
#define cn1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn1.txt"
#define cn2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn2.txt"
#define tw1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw1.txt"
#define tw2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw2.txt"
#define lus1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lus1.txt"
#define lus2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lus2.txt"
#define lcn1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lcn1.txt"
#define lcn2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lcn2.txt"
#define ltw1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\ltw1.txt"
#define ltw2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\ltw2.txt"
#define lout1 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lout1.txt"
#define lout2 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lout2.txt"
#define lout3 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lout3.txt"
#define lout4 "C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\lout4.txt"
#define false 0
#define true 1
#define line 1000

typedef int bool;

int str_get(FILE *in, FILE *out)
{ // separate function tool
    bool has_slash = false;
    char c;
    while (1)
    {
        c = fgetc(in);
        if (c == '"')
        {
            break;
        }
        else if (c == EOF)
        {
            return -1;
        }
    }
    while (1)
    {
        c = fgetc(in);
        if (c == '"')
        {
            if (!has_slash)
            {
                fprintf(out, "\n");
                break;
            }
            else
            {
                fprintf(out, "\\%c", c);
                has_slash = false;
            }
        }
        else if (c == '\\')
        {
            has_slash = true;
        }
        else if (c == EOF)
        {
            return -1;
        }
        else
        {
            fprintf(out, "%c", c);
            has_slash = false;
        }
    }
    return 1;
}

void separate(char *f_in, char *f_out1, char *f_out2)
{ // separate the txt file
    FILE *in = fopen(f_in, "r");
    FILE *out1 = fopen(f_out1, "w");
    FILE *out2 = fopen(f_out2, "w");
    while (1)
    {
        if (str_get(in, out1) == -1)
        {
            break;
        }
        str_get(in, out2);
    }
    fclose(in);
    fclose(out1);
    fclose(out2);
}

struct data
{ // order function tool
    char title[line], content[4 * line];
    struct data *parent, *left, *right;
};
typedef struct data dat; // order function tool

void binary(dat *work_node, dat *new)
{ // order function tool
    if (strcmp(work_node->title, new->title) <= 0)
    { // work < new
        if (work_node->right == NULL)
        {
            work_node->right = new;
            new->parent = work_node;
            return;
        }
        else
        {
            binary(work_node->right, new);
        }
    }
    else
    {
        if (work_node->left == NULL)
        {
            work_node->left = new;
            new->parent = work_node;
            return;
        }
        else
        {
            binary(work_node->left, new);
        }
    }
}

void list(FILE *in1, FILE *in2, dat **h)
{ // order function tool
    while (1)
    {
        dat *newone = (dat *)malloc(sizeof(dat));
        if (fscanf(in1, "%[^\n]%*c", newone->title) == EOF)
        {
            break;
        }
        fscanf(in2, "%[^\n]%*c", newone->content);
        newone->right = NULL;
        newone->left = NULL;
        newone->parent = NULL;

        if ((*h) == NULL)
        {
            (*h) = newone;
        }
        else
        {
            binary(*h, newone);
        }
    }
}

void l_output(dat *work_node, FILE *out1, FILE *out2)
{ // order function tool
    if (work_node == NULL)
        return;
    l_output(work_node->left, out1, out2);
    fprintf(out1, "%s\n", work_node->title);
    fprintf(out2, "%s\n", work_node->content);
    l_output(work_node->right, out1, out2);
}

void order(char *f_in1, char *f_in2, char *f_out1, char *f_out2)
{
    FILE *in1 = fopen(f_in1, "r");
    FILE *in2 = fopen(f_in2, "r");
    FILE *out1 = fopen(f_out1, "w");
    FILE *out2 = fopen(f_out2, "w");
    dat *hptr = NULL;
    list(in1, in2, &hptr);
    l_output(hptr, out1, out2);
    fclose(in1);
    fclose(in2);
    fclose(out1);
    fclose(out2);
}

void assemble(char *fa1, char *fa2, char *fb1, char *fb2, char *f_out1, char *f_out2)
{
    char tmp[4 * line], tmpa[line], tmpb[line];
    int a = 0, b = 0;
    FILE *a1 = fopen(fa1, "r");
    FILE *a2 = fopen(fa2, "r");
    FILE *b1 = fopen(fb1, "r");
    FILE *b2 = fopen(fb2, "r");
    FILE *out1 = fopen(f_out1, "w");
    FILE *out2 = fopen(f_out2, "w");

    a = fscanf(a1, "%[^\n]%*c", tmpa);
    b = fscanf(b1, "%[^\n]%*c", tmpb);
    while (1)
    {
        if (a == EOF && b == EOF)
        {
            break;
        }
        else if (a == EOF)
        {
            fscanf(b2, "%[^\n]%*c", tmp);
            fprintf(out1, "%s\n", tmpb);
            fprintf(out2, "%s\n", tmp);
            b = fscanf(b1, "%[^\n]%*c", tmpb);
        }
        else if (b == EOF)
        {
            fscanf(a2, "%[^\n]%*c", tmp);
            fprintf(out1, "%s\n", tmpa);
            fprintf(out2, "%s\n", tmp);
            a = fscanf(a1, "%[^\n]%*c", tmpa);
        }
        else
        {
            if (strcmp(tmpa, tmpb) > 0)
            { // fb1 before or equivalen
                fscanf(b2, "%[^\n]%*c", tmp);
                fprintf(out1, "%s\n", tmpb);
                fprintf(out2, "%s\n", tmp);
                b = fscanf(b1, "%[^\n]%*c", tmpb);
            }
            else if (strcmp(tmpa, tmpb) == 0)
            {
                fscanf(b2, "%[^\n]%*c", tmp);
                fprintf(out1, "%s\n", tmpb);
                fprintf(out2, "%s\n", tmp);
                fscanf(a2, "%[^\n]%*c", tmp);
                b = fscanf(b1, "%[^\n]%*c", tmpb);
                a = fscanf(a1, "%[^\n]%*c", tmpa);
            }
            else
            {
                fscanf(a2, "%[^\n]%*c", tmp);
                fprintf(out1, "%s\n", tmpa);
                fprintf(out2, "%s\n", tmp);
                a = fscanf(a1, "%[^\n]%*c", tmpa);
            }
        }
    }

    fclose(a1);
    fclose(a2);
    fclose(b1);
    fclose(b2);
    fclose(out1);
    fclose(out2);
}

void combine(char *f1, char *f2)
{
    char tmp1[line], tmp2[4 * line];
    int check_EOF;

    FILE *in1 = fopen(f1, "r");
    FILE *in2 = fopen(f2, "r");
    FILE *out = fopen(zh_tw, "w");
    fprintf(out, "{\n");
    while (1)
    {
        check_EOF = fscanf(in1, "%[^\n]%*c", tmp1);
        fscanf(in2, "%[^\n]%*c", tmp2);
        if (check_EOF == EOF)
        {
            break;
        }
        else
        {
            fprintf(out, "\"%s\": \"%s\",\n", tmp1, tmp2);
        }
    }
    fseek(out, -3, SEEK_END);
    fputs("\n", out);
    fprintf(out, "}");
    fclose(in1);
    fclose(in2);
    fclose(out);
}