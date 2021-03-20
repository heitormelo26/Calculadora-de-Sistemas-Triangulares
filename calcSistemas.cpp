#include<iostream>
#include<malloc.h>
#include<unistd.h>
#include<string>

using namespace std;

int triangularSuperior(float **sel, int n){
	for(int i = 0; i < n; i++){
        for(int j =0; j< n ; j++){
        	if(i>j && sel[i][j] != 0) return 0;
		}
    }
    return 1;
}

int triangularInferior(float **sel, int n){
	for(int i = 0; i < n; i++){
        for(int j =0; j< n ; j++){
        	if(i<j && sel[i][j] != 0) return 0;
		}
    }
    return 1;
}


float* caclSistemas(float **sel, int n, float *valor) {
	
	float solucao[n];
	float solucaoParcial = 0;
	float primeiraSolucao = 0;
	int k= 0;
	int aux ;
	int i ;
	int t = 0;
	
	int superior = triangularSuperior(sel,n);
	
	if( superior == 1){
		
		for( i = n-1; i >=0; i--){
	
			
			if( k == 0){
				if(sel[i][i] != 0){
					primeiraSolucao = valor[i]/sel[i][i];
				}
			
			}
			
			aux = k;
			solucaoParcial = valor[i];
			t = 0;
			
		
			while(aux>0){
													
				solucaoParcial = solucaoParcial - (sel[i][n-t-1] * solucao[n-1-t]);
				
				aux--;
				if(aux == 0 && i == (n-t-2) ) solucaoParcial = solucaoParcial/ sel[i][n-t-2];
				t++;
			}
			
			k++;
			
			if(i == (n-1)){
				solucao[i] = primeiraSolucao;
			}else{
				solucao[i] = solucaoParcial;
			}
		}
		
		cout<<"\n [ ";	
		for(int r = 0 ;r<n ;r++){
			if(n == 1){
				cout<<valor[r]/sel[r][r];
			}else{
				cout<< solucao[r];
			}
			if(r + 1 < n) cout<<", ";	
		} 
		cout<<"]";
			
	}else{
	int inferior = triangularInferior(sel,n);
	
	k = 0;
	solucaoParcial = 0;
	primeiraSolucao = 0;
	
	if(inferior == 1) {
		
		for( i = 0; i < n; i++){
	
			
			if( k == 0){
				if(sel[i][i] != 0){
					primeiraSolucao = valor[i]/sel[i][i];
				}
			
			}
			
			aux = k;
			solucaoParcial = valor[i];
			t = 0;
			
			while(aux>0){
											
				solucaoParcial = solucaoParcial - (sel[i][t] * solucao[t]);
					
				aux--;
				if(aux == 0 && (t+1) == i ){
					solucaoParcial = solucaoParcial/ sel[i][t+1];
				} 
				t++;
			}
			
			k++;
			
			if(i == 0){
				solucao[i] = primeiraSolucao;
			}else{
				solucao[i] = solucaoParcial;
			}
			
		}
		
		cout<<"\n [ ";	
		for(int r = 0 ;r<n ;r++){
			if(n == 1){
				cout<<valor[r]/sel[r][r];
			}else{
				cout<< solucao[r];
			}
			if(r + 1 < n) cout<<", ";	
		} 
		cout<<"]";
		
	}	
	}
	

}

	



int main(){
	
	int n,varQtd;

	cout<<"Todas as operacoes sao de +, entao para -, coloque o coeficiente como -:\n";
	cout<<"Digite a ordem do sistema quadrada: ";
	cin>> n;
	
	string var[n];
	float valor[n];
	int k=0;
	
	
	for(int i=0;i<n;i++){
		cout<<"\nDigite a "<<i+1<<" variavel: ";
		cin>> var[i];
	}
	
	float ** sel = (float**) malloc(n * sizeof(float*));
	
    if(sel == NULL)
    {
        printf("Matriz nao foi alocada...\n");
        exit(-1);
    }
    

    for(int i = 0; i < n; i++)
    {
        sel[i] = (float*) malloc(n * sizeof(float));
    }
    
    
    cout<<"\nInforme as equacoes do sistema:\n";
    
    
    for(int i = 0; i < n; i++){
    	
    	k = 0;
    	
        for(int j = 0; j< n ; j++){
        	
       		cout<<"\nEquacao "<<i+1<<": " ;
			cout<<"O coeficiente de "<<var[j]<<": ";
			cin>> sel[i][j];
		}
		
		cout<<"O valor da Equacao "<<i+1<<": ";
		cin>> valor[i];	
    }
        
    system("cls || clear");
    cout<<"\n Sistema: ";
    
    for(int i=0;i<n;i++){
    	
    	cout<<"\n Equacao "<<i+1<<": " ;
    	k=0;
    	
     	for(int j =0; j< n ; j++){
     		
			cout<<sel[i][j]<<var[j]<<" ";
			
				if(j+1 < n) {
				cout<<"+ ";
				k++;
				}
			}
			
		cout<<" = "<<valor[i];
	}
	
	int inferior = triangularInferior(sel,n);
	int superior = triangularSuperior(sel,n);
	if(superior == 1){
		cout<<"\n\n Sistema triangular Superior:\n";
		caclSistemas(sel,n,valor);
	}else{
		if(inferior == 1){
		cout<<"\n\n Sistema triangular Inferior:\n";
		caclSistemas(sel,n,valor);
		}else{
			cout<<"\nO sistema nao eh triangular, informe um sistema traingular:\n";
			sleep(3);
			exit(1);
		}
	}
	
}
