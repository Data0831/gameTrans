#include<stdio.h>
#include<stdlib.h>
#include"translate.h"

int main(){
    int type = 0;
    printf("please choose your type\n"
           "1.us\n"
           "2.us_cn\n"
           "3.us_tw\n"
           "4.us_cn_tw\n\n"
    );
    scanf("%d", &type);

    separate(us, us1, us2);
    switch(type){
        case 1: break;
        case 2: separate(cn, cn1, cn2);  break;
        case 3: separate(tw, tw1, tw2);  break;
        case 4: separate(cn, cn1, cn2);separate(tw, tw1, tw2);  break;
        default:    printf("Wrong!");system("pause");return 0;
    }
    
    system("code C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\us2.txt");
    system("start chrome C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\us2.txt");
    switch(type){
        case 1: break;
        case 2: system("code C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn2.txt");
        system("start chrome C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn2.txt");  break;
        case 3: system("code C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw2.txt");
        system("start chrome C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw2.txt");  break;
        case 4: system("code C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn2.txt");
        system("start chrome C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\cn2.txt");
        system("code C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw2.txt");
        system("start chrome C:\\Users\\Data\\Desktop\\PCL\\Mod_trans\\data\\tw2.txt");  break;
        default:    printf("Wrong!");system("pause");return 0;
    }
    printf("please translate the file\n");
    system("pause");

    order(us1, us2, lus1, lus2);
    switch(type){
        case 1: break;
        case 2: order(cn1, cn2, lcn1, lcn2);  break;
        case 3: order(tw1, tw2, ltw1, ltw2);  break;
        case 4: order(cn1, cn2, lcn1, lcn2);order(tw1, tw2, ltw1, ltw2);  break;
        default:    printf("Wrong!");system("pause");return 0;
    }
    printf("order");
    //system("pause");
    switch(type){
        case 1: break;
        case 2: assemble(lus1, lus2, lcn1, lcn2, lout1, lout2);  break;
        case 3: assemble(lus1, lus2, ltw1, ltw2, lout1, lout2);  break;
        case 4: assemble(lcn1, lcn2, ltw1, ltw2, lout3, lout4);
        assemble(lout3, lout4, ltw1, ltw2, lout1, lout2);  break;
        default:    printf("Wrong!");system("pause");return 0;
    }
    printf("assemble");
    //system("pause");
    switch(type){
        case 1: combine(lus1, lus2);break;
        case 2: combine(lout1, lout2);break;
        case 3: combine(lout1, lout2);break;
        case 4: combine(lout1, lout2);break;
        default:    printf("Wrong!");system("pause");return 0;
    }
    printf("combine");
    //system("pause");
    return 0;
}

