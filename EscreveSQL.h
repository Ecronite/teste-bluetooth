#ifndef E_SQL
#define E_SQL

class EscreveSQL
{
private:
    MySQL_Connection*  conn;
    
public:
    EscreveSQL(MySQL_Connection*);
    ~EscreveSQL();

    void inserir(char* placa, int pessoas);
    void deletar(char* condicao);
    void atualizar(char* pelo_que, char* condicao);
};

EscreveSQL::EscreveSQL(MySQL_Connection* conn) : conn(conn)
{
}

EscreveSQL::~EscreveSQL()
{ 
}

void EscreveSQL::inserir(char* placa, int pessoas)
{
    char comando[100];
    sprintf(comando, "INSERT INTO onibus VALUES ('%c', '%d')",placa, pessoas);

    MySQL_Cursor* mensageiro = new MySQL_Cursor(conn);

    if(mensageiro->execute(comando))
        Serial.print("comando efetivado com sucesso!");

    else
        Serial.print("Falha no comando");
    delete mensageiro;
}

void EscreveSQL::deletar(char* condicao)
{
	
	char comando[100];
	sprintf(comando, "DELETE FROM onibus WHERE %c", condicao);
	
    //char* comando = {("DELETE FROM teste.onibus WHERE %c" ,condicao)};
    
    MySQL_Cursor* mensageiro = new MySQL_Cursor(conn);
    
    if(mensageiro->execute(comando)) 
        Serial.print("comando efetivado com sucesso!");

    else
        Serial.print("Falha no comando");

    delete mensageiro;
}

void EscreveSQL::atualizar(char* o_que, char* condicao)
{
    char comando[100];
    sprintf(comando, "UPDATE onibus SET %c WHERE %c" ,o_que ,condicao);
    //char* comando = {("UPDATE teste.onibus SET %c WHERE %c" ,o_que ,condicao)};
    
    MySQL_Cursor* mensageiro = new MySQL_Cursor(conn);
    if(mensageiro->execute(comando))
        Serial.print("comando efetivado com sucesso!");

    else
        Serial.print("Falha no comando");

    delete mensageiro;
}

#endif
