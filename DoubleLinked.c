/*
	MUHAMMAD ALFIN FARHANSYAH
	50421907
	2IA21
	DOUBLE LINKED LIST MENGGUNAKAN BAHASA C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mahasiswa{
	int nim; //menampung integer nim mahasiswa
	char nama[30]; //menampung karakter nama mahasiswa
	struct mahasiswa *next, *prev; //menampung alamat data selanjutnya (next) dan sebelumnya (prev)
}*head, *tail, *current;
//head => pointer yang menyimpan alamat data pertama
//tail => pointer yang menyimpan alamat data terakhir
//current => pointer yang digunakan sebagai temporary variabel

void pushHead(int nim, char nama[]){
    //alokasi memory untuk data baru
	current = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));
	current->nim = nim; //assign data ke dalam struct
	strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama

	//set penunjuk data lain yang menjadi NULL dulu
	current->next = current->prev=NULL;

	if(head == NULL){ //jika nilai head adalah null, maka set head = tail = current
		head = tail = current; //set nilai head = tail = current
	}
	else{ //jika nilai head tidak null, maka
        head->prev = current;
		current->next = head; //set nilai current->next = head
		head = current; //kemudian set nilai head = current
	}
}

void pushTail(int nim, char nama[]){
	current = (struct mahasiswa*)malloc(sizeof(struct mahasiswa)); //alokasi memory untuk data baru
	current->nim = nim;//assign data ke dalam struct
	strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama

	//set penunjuk data yang lain menjadi NULL dulu
	current->prev = current->next = NULL;

	if(head == NULL){ //jika nilai head adalah null, maka set head = tail = current
		head = tail = current; //set nilai head = tail = current
	}
	else{ //jika nilai head tidak null, maka
        current->prev = tail;
		tail->next = current; //set nilai tail->next = current
		tail = current; //kemudian set nilai tail = current
	}
}

void PushMid(int nim, char nama[]){
	if(head==NULL){ //cek apakah head NULL atau bukan, jika NULL
		pushHead(nim,nama); //tambahkan data di depan
	}else if(nim < head->nim){ //jika nim yang dimasukkan lebih kecil dari nim data ke head
		pushHead(nim,nama); //tambahkan data di depan
	}else if(nim > tail->nim){ //jika nim yang dimasukkan lebih kecil dari nim data ke tail
		pushTail(nim,nama); //tambahkan data di belakang
	}else{ //jika kondisinya selain di atas
		current = (struct mahasiswa*)malloc(sizeof (struct mahasiswa)); //buat blok data
		current->nim = nim; //assign data ke dalam struct
        strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama
		current->next = current->prev = NULL; //set penunjuk data sebelum/sesudahnya menjadi NULL dulu

		struct mahasiswa *temp=head; //set temp sebagai head
		while(temp!=NULL && temp->nim< current->nim){ //mencari posisi data akan dimasukkan
			temp=temp->next;
		}
		//set data penunjuk alamat-alamat data ke selanjutnya/sebelumnya
		current->prev=temp->prev;
		current->next=temp;

		temp->prev->next=current;
		temp->prev=current;
	}
}

void popHead(){
	if(head==NULL){ //jika head bernilai null
		printf("No data\n"); //tampilkan info tidak ada data
	}else if(head==tail){ //jika nilai head = tail
        current=head; //set current sebagai head
		head=tail=NULL; //set nilai head = tail = null
		free(current); //hapus nilai current (head)
	}else{ //jika nilai head bukan null dan bukan tail
        current=head; //set current sebagai head
		head=head->next; //set nilai head menjadi data selanjutnya dari head
		head->prev=NULL; //set head sebelumnya menjadi NULL
		free(current);// hapus nilai current (head)
	}
}

void popTail(){
	if(head==NULL){ //jika nilai head = null
		printf("No data\n"); //tampilkan info tidak ada data
	}else if(head==tail){ //jika nilai head = tail
        current=tail; //set nilai current dengan tail
		head=tail=NULL; //set nilai head = tail = null
		free(current); //hapus nilai current
	}else{ //jika nilai head bukan null dan bukan tail
		current=tail; //set nilai current menjadi tail
		tail=tail->prev; //set nilai setelah next menjadi null/pointer next punya tail diset null
		tail->next=NULL; //set nilai setelah next menjadi null/pointer next punya tail diset null
		free(current); //hapus nilai current
	}
}

void popMid(int nim){
	int ketemu=0; //inisialisasi flag ketemu untuk ngecek data ada atau tidak
	if(head==NULL){ //jika head bernilai NULL
		printf("No Data\n"); //tampilkan info tidak ada data
	}else{ //jika head tidak NULL
		current=head; //set current dengan head
		while(current!=NULL){ //mencari posisi data yang ada
			//cek data,jika ditemukan, ganti flag dan hentikan looping
			if(current->nim==nim){
				ketemu=1;
				break;
			}
			current=current->next; //set current dengan nilai selanjutnya
		}

		if(ketemu==1){ //jika data ketemu
			if(current==head){ //jika data yang ditemukan adalah Head
				popHead(); //hapus head/data pertama
			}else if(current==tail){ //jika data yang ditemukan adalah Tail
				popTail(); //hapus tail/data terakhir
			}else{ //jika data yang ditemukan bukan Head dan bukan Tail
				current->prev->next=current->next; //set current next
				current->next->prev=current->prev; // set current prev
				free(current); //hapus nilai current
			}
		}else{ //jika data tidak ketemu, tampilkan info data tidak ada
			printf("Not Found\n");
		}
	}
}

void print(){
	current = head; //set current sebagai head
	if(current!=NULL){
        while(current != NULL){ //looping selama current bukan null
            printf("%s -> %d\n",current->nama,current->nim); //tampilkan nilai nama dan nim
            current = current->next; //set current menjadi nilai setelahnya
        }
	} else{
        printf("No Data\n");
	}
}

void main(){
	pushHead(111, "Alfin");
	pushTail(222, "Bedul");
	pushTail(333,"Joni");
	pushTail(444,"Bunga");
	pushHead(555, "David");
	PushMid(666, "Budi");
	print();
	printf("\n-----------------------------------------\n");
	popMid(555);
	print();
	getchar();
}
