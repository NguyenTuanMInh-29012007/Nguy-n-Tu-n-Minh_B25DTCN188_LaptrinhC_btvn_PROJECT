#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 100

struct room{
	char roomId[5];
	int type;
	double price;
	int status;
}; 

struct date{
	int day;
	int month;
	int year;
};

struct booking{
	int bookId;
	char roomId[5];
	char customerName[50];
	int days;
	double totalCost;
	struct date date;
};

void addSampleRooms(struct room room[], int *n){ 
    struct room avaiable[] = {
        {"101", 1, 350, 0},
        {"102", 2, 500, 0},
        {"201", 1, 450, 1},
        {"202", 2, 700, 2},
        {"301", 1, 500, 1},
        {"302", 1, 150, 0},
        {"401", 2, 600, 2},
        {"402", 1, 550, 2},
        {"403", 2, 250, 0},
    };

    int size = sizeof(avaiable)/sizeof(avaiable[0]);
    for(int i=0;i<size;i++){
        room[*n] = avaiable[i];
        (*n)++;
    }
}

void addRoom(struct room room[],int *n){ 
	
	while(1){
    printf("\nNhap so phong (ID) - 'MAX:3-4 ki tu': ");
		gets(room[*n].roomId);
		int length = strlen(room[*n].roomId);
		if(length<3 || length>4){
			printf("\nLoi! So phong chi co (3-4) ky tu!");
			printf("\nBan phai nhap DUNG So Phong, xin luu y!\n"); 
			continue;
		}
    	for(int i=0;i<*n;i++){
		 	if(strcmp(room[i].roomId, room[*n].roomId)==0){
				printf("\nPhong %s da ton tai",room[i].roomId);
				return;
		}
		}
		break; 
	}
			
	while(room[*n].type !=1 && room[*n].type!=2){
		printf("\nNhap loai phong (1.Don // 2.Doi): ");
		scanf("%d",&room[*n].type);
		getchar();
		if(room[*n].type !=1 && room[*n].type!=2){
			printf("\nLoi loai phong CHI duoc chon 1(Don) hoac 2(Doi)!");
		}				
	}
	
	do{
		printf("Nhap gia phong: ");
		scanf("%lf",&room[*n].price);
		getchar();
		if(room[*n].price<=0){
			printf("\nLoi: Gia phong phai LON HON (>) 0!\n");
		}	
	}while(room[*n].price<=0);
	
	room[*n].status=0;			
    (*n)++;
    
    printf("\nThem phong thanh cong! Phong %s da duoc tao voi trang thai Trong.",room[*n-1].roomId);
}

void update(struct room room[],int *n){
	char roomId[5];
	printf("Nhap so phong (ID) can cap nhat: ");
	fgets(roomId,5,stdin);
	roomId[strcspn(roomId,"\n")] = '\0';	
	
	int index = -1;
	for(int i=0;i<*n;i++){
		if(strcmp(room[i].roomId,roomId)==0){
			index = i;
			break;
		}
	}
	if(index==-1){
		getchar();
		printf("\nLoi: Khong tim thay so phong (RoomId) phong ban vua nhap");
	}else if(room[index].status==1){
		printf("\nPhong %s da co KHACH khong the UPDATE",room[index].roomId);
	}else{
		printf("Nhap loai phong moi (1.Don // 2.Doi): ");
	    scanf("%d",&room[index].type);
	    getchar();
	    
	    if(room[index].type !=1 && room[index].type!=2){
		    printf("\nLoi loai phong chi duoc chon 1(Don) hoac 2(Doi)!");
		    return;
	}	
	
	printf("Nhap gia phong moi: ");
	scanf("%lf",&room[index].price);
	getchar();
	if(room[index].price<=0){
		printf("\nLoi: Gia phong phai lon hon 0!");
		return;	
	}	
		printf("\nCap nhat thong tin phong thanh cong!");
	}
}

void  lock(struct room room[],int *n){ 
	char roomId[5];
	printf("\nNhap so phong (ID) can bao tri:");
	fgets(roomId,5,stdin);
	roomId[strcspn(roomId,"\n")] = '\0';	
	
	int index=-1;
	for(int i=0;i<*n;i++){
		if(strcmp(room[i].roomId,roomId)==0){
			index =i;
			break;
		}
	}
	if(index==-1){
		getchar(); 
		printf("\nKhong tim thay phong %s !",roomId);
	}else{
		if(room[index].status == 1){
			printf("\nPhong %s da co Khach!, khong the bao tri.",roomId);
			return;
		}else if(room[index].status ==2){
			printf("\nPhong %s da o che do BAO TRI!",roomId);
			return;
		}	
		room[index].status=2;
		printf("Phong %s da duoc chuyen sang che do BAO TRI!",roomId);	
	}
} 

void displayRoomsPaging(struct room room[], int n){ 
    int page = 1;
    int pageSize = 10; 
    int totalPage = n/pageSize + (n%pageSize==0?0:1);
    
    
    
    int choice;
    do{
        system("cls");
        printf("\nLoai phong (1.Don , 2.Doi)");
        printf("\nTrang thai (0:Trong , 1:Co Khach , 2:Bao tri)\n");
        printf("\n*================= DANH SACH PHONG (Page %d/%d) ===================*\n", page, totalPage);

        int start = (page - 1) * pageSize;
        int end = (start + pageSize < n) ? start + pageSize : n;
       
        printf("|%-2s| %-13s|%-2s|   %-16s|%-14s|\n","STT","So Phong","Loai phong","Gia tien","Trang Thai");
        printf("*----------------------------------------------------------------*\n");
        
        char typeStr[10], statusStr[20];
        for(int i = start; i < end; i++){
		if(room[i].status==0) strcpy(statusStr,"Trong");
		else if(room[i].status==1) strcpy(statusStr,"Co Khach");
		else strcpy(statusStr,"Bao tri");
		    	
            printf("|%-2d.| Phong %-5s  | Loai %-2d  |Gia %-10.3lf VND | %-12s |\n",
                   i + 1, room[i].roomId, room[i].type, room[i].price, statusStr);
        }

        printf("*===*==============*==========*===================*==============*\n");
        printf("\n1. Trang truoc");
        printf("\n2. Trang sau");
        printf("\n0. Quay lai MENU");
        printf("\nNhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice){
        	case 1:{
        		if(page>1){
        			page--;
				}else{
					printf("\nDanh sach khong ton tai o trang TRUOC!");
					printf("\nNhan Enter de tiep tuc..."); 
					getchar(); 					
				}       		
				break;
			}
        	case 2:{
        		if(page<totalPage){
        			page++;
				}else{
					printf("\nDanh sach khong ton tai o trang SAU!");
					printf("\nNhan Enter de tiep tuc..."); 
					getchar(); 
				}    		
				break;
			}
        	case 0:{
				return;
			}
        	default:{
        		printf("\nLoi.Lua chon khong hop le!");   	
        		printf("\nNhan Enter de tiep tuc..."); 
				getchar();			 		
			}			
		}
    }while(1);
}

void find(struct room room[],int *n){
	int type;
	
	while(type !=1 && type!=2){
	printf("\nNhap loai phong (1.Don // 2.Doi): ");
	scanf("%d",&type);
	getchar();
	if(type !=1 && type!=2){
		printf("\nLoi loai phong CHI duoc chon 1(Don) hoac 2(Doi)!");
	}				
	}
	
	printf("\n*=== Danh sach phong con TRONG ====*"); 
	int flag = 0; 
	for(int i=0;i<*n;i++){
		if(room[i].type==type && room[i].status==0){
			printf("\n|Phong %s | Loai %d | Gia: %.3lf |",room[i].roomId,room[i].type,room[i].price);
			printf("\n*----------*--------*--------------*");
			flag=1;
		}
	}
	if(!flag){
		printf("\nKhong co phong nao phu hop!");
	} 
}

void BubbleSort(struct room room[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(room[j].price < room[j+1].price){
			struct room temp = room[j];
			room[j] = room[j+1];
			room[j+1] = temp;				
			}
		}
	}
} 

void checkIn(struct room room[],int *n,struct booking bk[],int *count){
	int bookId;
	char roomId[5];
	char customerName[50];
	int days;
	struct date date;
	
	while(1){
		printf("\nNhap so phong: ");
		fflush(stdin);
		gets(roomId);
		int length = strlen(roomId);
		
		if(length<3 || length>4){
			printf("\nLoi! So phong chi co (3-4) ky tu!");
			printf("\nBan phai nhap DUNG So Phong, xin luu y!\n"); 
			continue;
		}
		while(1){
      	char ch;
		printf("\nBan co muon tiep tuc khong ('c' hay 'k'): ");
		scanf(" %c",&ch);
		getchar();
		if(ch=='c'){
			break;
		}else if(ch=='k'){
			printf("\nNhan Enter de thoat...");						
			return;
		}else{
			printf("\nLua chon khong hop le!");
		}
		if(ch=='k')
		break; 		
		}
		int index=-1;
    	for(int i=0;i<*n;i++){
		 	if(strcmp(room[i].roomId, roomId)==0){
				index = i;
				break;
			}
		}
		if(index==-1){
			printf("Khong tim thay phong %s\n",roomId);
			continue; 
		}else{
			if(room[index].status==1){
				printf("\nPhong %s da co KHACH \nNhan Enter de tiep tuc... ",room[index].roomId);
				continue; 
			}
			if(room[index].status==2){
				printf("\nPhong %s da duoc BAO TRI \nNhan Enter de tiep tuc... ",room[index].roomId);
				continue; 
			}
			if(room[index].status==0){
				printf("\nPhong %s con TRONG",room[index].roomId);
				printf("\nChao mung ban den voi dich vu HOTEL cua chung toi!\n");
				
				while(1){
				printf("\nNhap ten (costumer): ");
				fgets(customerName,50,stdin);
				customerName[strcspn(customerName,"\n")] = '\0';
				
				if(strlen(customerName)==0){
					printf("\nLoi: Khong duoc de trong! Moi nhap lai.");
					continue;
				}		
					
				char ch;	
				while(1){			
				printf("Ban co CHAC CHAN voi Name do khong? ('c' hoac 'k'): ");
				scanf(" %c",&ch);
				getchar();
				if(ch=='c'){
					break;
				}else if(ch=='k'){
					break;
				}else{
					printf("\nLua chon khong hop le! Moi ban nhap lai!\n");
					continue;
					}					 												
				}	
					if(ch=='c')
					break;										
				}
				
				int result;
				do {
 				    printf("Nhap so ngay o: ");
  				    result = scanf("%d", &days);
    
   			     	if(result != 1){ 
      				    printf("\nLoi: Ban phai nhap mot so nguyen!\n");
       		   			while(getchar() != '\n'); 
       				    continue;
   				}    
  			    if(days <= 0){
       			    printf("\nSo ngay o phai lon hon 0!\n");
     			    continue;
    			}
    			break; 
				} while(1);
				
				while(1){
					printf("Ngay nhan phong (dd/mm/yyyy): ");
					scanf("%d/%d/%d",&bk[*count].date.day,&bk[*count].date.month,&bk[*count].date.year);
					int success=1;
					if(bk[*count].date.year<2025 || bk[*count].date.year>2030){
						printf("\nNam(Year) vua nhap khong hop le!");
						success=0;
					}else{
						if(bk[*count].date.month<1 || bk[*count].date.month>12){
							printf("\nThang (Month) vua nhap khong hop le!");
							success=0;
						}else{
							if(bk[*count].date.month==1 || bk[*count].date.month==3 || bk[*count].date.month==7 || bk[*count].date.month==8 || bk[*count].date.month==10 || bk[*count].date.month==12){
								if(bk[*count].date.day<1 || bk[*count].date.day>31){
									printf("\nNgay (day) khong hop le!");
									success=0;
								}
							}
							if(bk[*count].date.month==4 || bk[*count].date.month==6 || bk[*count].date.month==9 || bk[*count].date.month==11){
								if(bk[*count].date.day<1 || bk[*count].date.day>30){
									printf("\nNgay (day) khong hop le!");
									success=0;
								}
							}
							if(bk[*count].date.month==2){
								if(bk[*count].date.year%4==0 && bk[*count].date.year%100!=0 || bk[*count].date.year%400==0){
									if(bk[*count].date.day<1 || bk[*count].date.day>29){
										printf("\nNgay (day) khong hop le!");
										success=0;
									}
								}else{
									if(bk[*count].date.day<1 || bk[*count].date.day>28){
										printf("\nNgay (day) Khong hop le!");
										success=0;
									}
								}
							}
						}
					}
					if(success)
					break;
				}
			}
		}
		printf("\nCheck-In thanh cong! Ma dat phong %s\n",room[index].roomId);
		room[index].status=1;
		bk[*count].bookId = *count + 1;
		strcpy(bk[*count].roomId, roomId);
		strcpy(bk[*count].customerName, customerName);
		bk[*count].days = days;
		bk[*count].totalCost = days * room[index].price;

		(*count)++;
		
		printf("\n----------------Hoa don chi tiet---------------");
		printf("\n|Ma dat phong: %d",bk[*count-1].bookId);
		printf("\n|So phong: %-5s",roomId);
		printf("\n|Khach hang (Customer): %-30s",customerName);
		printf("\n|Ngay nhan: %d/%d/%d",bk[(*count)-1].date.day,bk[(*count)-1].date.month,bk[(*count)-1].date.year);
		printf("\n|So ngay: %d ngay",days);
		printf("\n|Tong tien: %-3.3lf VND",bk[(*count)-1].totalCost);
		printf("\n-----------------------------------------------");
		
		break; 
	}	
} 

void PaymentHistory(struct booking bk[],int count,struct room room[],int *n){
	if(count==0){
		printf("\nChua co hoa don nao duoc tao!");
		printf("\nNhan Enter de tiep tuc...");
		return;
	}
	char roomId[5];
	while(1){
		printf("\nNhap so phong: ");
		fflush(stdin);
		gets(roomId);
		int length = strlen(roomId);
		
		if(length<3 || length>4){
			printf("\nLoi! So phong chi co (3-4) ky tu!");
			printf("\nBan phai nhap DUNG So Phong, xin luu y!\n"); 
			continue;
		}
		int index=-1;
    	for(int i=0;i<*n;i++){
		 	if(strcmp(room[i].roomId, roomId)==0){
				index = i;
				break;
			}
		}
		if(index==-1){
			printf("phong %s khong ton tai!\n",roomId);
			continue;	
		}
		for(int i=0;i<count;i++){
			if(strcmp(bk[i].roomId,roomId)==0){
				count++;
			}
		}
		    int flag = 0;
   				printf("\n============================= LICH SU THANH TOAN =============================\n");
   				printf("|%-10s |%-25s |%-8s |%-8s |%-15s |\n",
           				"So Phong", "Khach Hang", "Ngay nhan", "So Ngay", "Tong Tien");
           		printf("------------------------------------------------------------------------------\n");		

   			for (int i = 0; i < count; i++) {
        		if (strcmp(bk[i].roomId, roomId) == 0) {
           			printf("|%-10s |%-25s |%02d/%02d/%04d| %-8d|%-12.3lf VND|\n",
                    bk[i].roomId, bk[i].customerName,
                    bk[i].date.day, bk[i].date.month, bk[i].date.year,
                    bk[i].days, bk[i].totalCost);
            	flag = 1;
     			printf("==============================================================================\n");           	
        		}
  			}
   			if (!flag) {
        		printf("\nPhong %s chua co hoa don nao!\n", roomId);
    		}
    	while(1){
      	char ch;
		printf("\nBan co muon tiep tuc khong ('c' hay 'k'): ");
		scanf(" %c",&ch);
		getchar();
		if(ch=='c'){
			break;
		}else if(ch=='k'){
			printf("\n\nNhan Enter de tro lai MENU...");			
			return;
		}else{
			printf("\nLua chon khong hop le!");
		}
		if(ch=='k')
		break; 		
		}
	}
}

int getMenuChoice() {
    char input[100];

    while (1) {
        printf("\nMoi ban nhap lua chon: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';    
		  
        if (strlen(input) == 0) {
            printf("Loi! Khong duoc de trong. Hay nhap lai.\n");
            continue;
        }     
        int isDigit = 1;
        for (int i = 0; i < strlen(input); i++){
            if (!isdigit(input[i])) {
                isDigit = 0;
                break;
            }
        }
        if (!isDigit) {
            printf("Loi! Chi duoc nhap so. Hay nhap lai.\n");
            continue;
        }
        int choice = atoi(input);
        return choice;
    }
}

int main(){
	int n=0;
	int count=0;
	int choice;
	struct room room[MAX];
	struct booking booking[MAX];
		
	addSampleRooms(room,&n);
	
	do{
		system("cls");
		printf("\n========= HE THONG QUAN LY HOTEL ===========");
		printf("\n|1.Them phong moi                          |");
		printf("\n--------------------------------------------");
		printf("\n|2.Cap nhat phong                          |");
		printf("\n--------------------------------------------");
		printf("\n|3.Bao tri phong(Khoa)                     |");
		printf("\n--------------------------------------------");
		printf("\n|4.Hien thi danh sach                      |");
		printf("\n--------------------------------------------");
		printf("\n|5.Tim kiem                                |");
		printf("\n--------------------------------------------");
		printf("\n|6.Sap xep danh sach phong(Theo gia phong) |");
		printf("\n--------------------------------------------");
		printf("\n|7.Check-in(Giao dich)                     |");
		printf("\n--------------------------------------------");
		printf("\n|8.Lich su thue phong                      |");
		printf("\n--------------------------------------------");
		printf("\n|9.Thoat MENU                              |");
		printf("\n============================================");
		choice = getMenuChoice();
		
		switch(choice){
			case 1:{
				addRoom(room,&n);
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();
				break;
			}
			case 2:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					update(room,&n);
				}
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();				
				break;
			}
			case 3:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					lock(room,&n);
				}	
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();								
				break;
			}
			case 4:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					displayRoomsPaging(room,n);
				}	
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();								
				break;
			}
			case 5:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					find(room,&n);
				}	
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();									
				break;
			}
			case 6:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					BubbleSort(room,n);
					printf("\nCap nhat gia phong thanh cong!");
					printf("\nNhan Enter de hien thi ra danh sach!");
					getchar();
					displayRoomsPaging(room,n);
				}	
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();								
				break;
			}
			case 7:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					checkIn(room, &n,booking, &count);
					getchar();
				}	
				printf("\nNhan Enter de quay lai MENU...");
				getchar();							
				break;
			}
			case 8:{
				if(n==0){
					printf("\nCan cap nhat so phong truoc!. Khong co (RoomId) nao ton tai!");
					getchar();
				}else{
					PaymentHistory(booking,count,room,&n);	
					getchar();
				}								
				break;
			}
			case 9:{
				printf("\nCam on ban da su dung dich vu cua Hotel chung toi!");
				printf("\nHen gap lai!");
				exit(0);
				break;
			}
			default:{
				printf("\nLua chon cua ban khong hop le!");
				printf("\n\nNhan Enter de tiep tuc...");
				getchar();
				break;
			}
		}		
	}while(1);
return 0;
}
