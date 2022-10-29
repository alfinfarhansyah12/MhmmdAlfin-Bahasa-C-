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
	int npm; //menampung integer npm mahasiswa
	char nama[30]; //menampung karakter nama mahasiswa
	struct mahasiswa *next, *prev; //menampung alamat data selanjutnya (next) dan sebelumnya (prev)
}*head, *DataAkhir, *current;
//head => pointer yang menyimpan alamat data pertama
//DataAkhir => pointer yang menyimpan alamat data terakhir
//current => pointer yang digunakan sebagai temporary variabel

void pushHead(int npm, char nama[]){
    //alokasi memory untuk data baru
	current = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));
	current->npm = npm; //assign data ke dalam struct
	strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama

	//set penunjuk data lain yang menjadi NULL dulu
	current->next = current->prev=NULL;

	if(head == NULL){ //jika nilai head adalah null, maka set head = DataAkhir = current
		head = DataAkhir = current; //set nilai head = DataAkhir = current
	}
	else{ //jika nilai head tidak null, maka
        head->prev = current;
		current->next = head; //set nilai current->next = head
		head = current; //kemudian set nilai head = current
	}
}

void pushDataAkhir(int npm, char nama[]){
	current = (struct mahasiswa*)malloc(sizeof(struct mahasiswa)); //alokasi memory untuk data baru
	current->npm = npm;//assign data ke dalam struct
	strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama

	//set penunjuk data yang lain menjadi NULL dulu
	current->prev = current->next = NULL;

	if(head == NULL){ //jika nilai head adalah null, maka set head = DataAkhir = current
		head = DataAkhir = current; //set nilai head = DataAkhir = current
	}
	else{ //jika nilai head tidak null, maka
        current->prev = DataAkhir;
		DataAkhir->next = current; //set nilai DataAkhir->next = current
		DataAkhir = current; //kemudian set nilai DataAkhir = current
	}
}

void PushMid(int npm, char nama[]){
	if(head==NULL){ //cek apakah head NULL atau bukan, jika NULL
		pushHead(npm,nama); //tambahkan data di depan
	}else if(npm < head->npm){ //jika npm yang dimasukkan lebih kecil dari npm data ke head
		pushHead(npm,nama); //tambahkan data di depan
	}else if(npm > DataAkhir->npm){ //jika npm yang dimasukkan lebih kecil dari npm data ke DataAkhir
		pushDataAkhir(npm,nama); //tambahkan data di belakang
	}else{ //jika kondisinya selain di atas
		current = (struct mahasiswa*)malloc(sizeof (struct mahasiswa)); //buat blok data
		current->npm = npm; //assign data ke dalam struct
        strcpy(current->nama, nama); //copy nilai variabel parameter nama ke current->nama
		current->next = current->prev = NULL; //set penunjuk data sebelum/sesudahnya menjadi NULL dulu

		struct mahasiswa *temp=head; //set temp sebagai head
		while(temp!=NULL && temp->npm< current->npm){ //mencari posisi data akan dimasukkan
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
		printf("Tidak dapat menemukan data user\n"); //tampilkan info tidak ada data
	}else if(head==DataAkhir){ //jika nilai head = DataAkhir
        current=head; //set current sebagai head
		head=DataAkhir=NULL; //set nilai head = DataAkhir = null
		free(current); //hapus nilai current (head)
	}else{ //jika nilai head bukan null dan bukan DataAkhir
        current=head; //set current sebagai head
		head=head->next; //set nilai head menjadi data selanjutnya dari head
		head->prev=NULL; //set head sebelumnya menjadi NULL
		free(current);// hapus nilai current (head)
	}
}

void popDataAkhir(){
	if(head==NULL){ //jika nilai head = null
		printf("Tidak dapat menemukan data user\n"); //tampilkan info tidak ada data
	}else if(head==DataAkhir){ //jika nilai head = DataAkhir
        current=DataAkhir; //set nilai current dengan DataAkhir
		head=DataAkhir=NULL; //set nilai head = DataAkhir = null
		free(current); //hapus nilai current
	}else{ //jika nilai head bukan null dan bukan DataAkhir
		current=DataAkhir; //set nilai current menjadi DataAkhir
		DataAkhir=DataAkhir->prev; //set nilai setelah next menjadi null/pointer next punya DataAkhir diset null
		DataAkhir->next=NULL; //set nilai setelah next menjadi null/pointer next punya DataAkhir diset null
		free(current); //hapus nilai current
	}
}

void popMid(int npm){
	int ketemu=0; //inisialisasi flag ketemu untuk ngecek data ada atau tidak
	if(head==NULL){ //jika head bernilai NULL
		printf("Tidak dapat menemukan data user\n"); //tampilkan info tidak ada data
	}else{ //jika head tidak NULL
		current=head; //set current dengan head
		while(current!=NULL){ //mencari posisi data yang ada
			//cek data,jika ditemukan, ganti flag dan hentikan looping
			if(current->npm==npm){
				ketemu=1;
				break;
			}
			current=current->next; //set current dengan nilai selanjutnya
		}

		if(ketemu==1){ //jika data ketemu
			if(current==head){ //jika data yang ditemukan adalah Head
				popHead(); //hapus head/data pertama
			}else if(current==DataAkhir){ //jika data yang ditemukan adalah DataAkhir
				popDataAkhir(); //hapus DataAkhir/data terakhir
			}else{ //jika data yang ditemukan bukan Head dan bukan DataAkhir
				current->prev->next=current->next; //set current next
				current->next->prev=current->prev; // set current prev
				free(current); //hapus nilai current
			}
		}else{ //jika data tidak ketemu, tampilkan info data tidak ada
			printf("Tidak dapat menemukan data user\n");
		}
	}
}

void print(){
	current = head; //set current sebagai head
	if(current!=NULL){
        while(current != NULL){ //looping selama current bukan null
            printf("%s -> %d\n",current->nama,current->npm); //tampilkan nilai nama dan npm
            current = current->next; //set current menjadi nilai setelahnya
        }
	} else{
        printf("Tidak dapat menemukan data user\n");
	}
}

void main(){
	printf("\n-----------------------------------------\n");
	printf("	MUHAMMAD ALFIN FARHANSYAH\n");
	printf("	50421907\n");
	printf("	2IA25\n");
	printf("Contoh Double List Linked Pemerograman C\n");
	printf("\n-----------------------------------------\n");
	pushHead(50421907, "Muhammad Alfin Farhansyah");
	pushDataAkhir(5544555, "Rizaldi Komeng Kurniawan");
	pushDataAkhir(5434313,"David Wilson AlekYonglek");
	pushDataAkhir(5465434,"Bunga");
	pushHead(3445544, "Supradi Neneng Markoneng");
	PushMid(7654344, "Joni Siregar");
	print();
	printf("\n-----------------------------------------\n");
	popMid(6555565);
	print();
	getchar();
}
