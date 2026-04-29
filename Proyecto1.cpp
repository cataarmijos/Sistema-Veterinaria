#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

class Dueno;
class Veterinario;
class Mascota;
class Servicio;
class Cita;

class Persona {
	protected:
	    string nombre;
	    string telefono;
	    string email;
	public:
		//Constructor
	    Persona (const string& nombre, const string& telefono, const string& email) : nombre (nombre), telefono (telefono), email (email) {}
	
		//Getters
	    string getNombre () const { 
			return nombre; 
		}
	    string getTelefono () const { 
			return telefono; 
		}
	    string getEmail () const { 
			return email; 
		}
	
		 //Setters
	    void setNombre (const string& n_nombre) { 
			nombre = n_nombre; 
		}
	    void setTelefono (const string& n_telefono) { 
			telefono = n_telefono; 
		}
	    void setEmail (const string& n_email) { 
			email = n_email; 
		}
	
		//Metodos Virtuales puros
	    virtual void mostrarInfo () const = 0;
	    
	    //Destructor
	    virtual ~Persona () {}
};

class Usuario {
	protected:
	    string idSistema;
	    string contrasena;
	    string rol;
	public:
		//Constructor
	    Usuario (const string& idSistema, const string& contrasena, const string& rol) : idSistema (idSistema), contrasena (contrasena), rol (rol) {}
		
		//Getters
	    string getIdSistema () const { 
			return idSistema; 
		}
	    string getContrasena () const { 
			return contrasena; 
		}
	    string getRol () const { 
			return rol; 
		}
	    
	    //Setters
	    void setContrasena (const string& n_contrasena) { 
			contrasena = n_contrasena; 
		}
	    
	    //Destructor
	    virtual ~Usuario () {}
};

class Administrador : public Persona, public Usuario {                                                                    // CAMBIADO DESDE AQUI 
private:
    static int contadorAdmin;

    static string generarIdSistema() {
        stringstream ss;
        ss << "ADM" << setfill('0') << setw(3) << ++contadorAdmin;
        return ss.str();
    }

public:
    Administrador(const string& nombre, const string& telefono, const string& email, const string& contrasena)
        : Persona(nombre, telefono, email),
          Usuario(generarIdSistema(), contrasena, "Administrador") {}

    void mostrarInfo() const override {
        cout << "\n--- ADMINISTRADOR ---" << endl;
        cout << "ID: " << idSistema << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Email: " << email << endl;
    }
};

int Administrador::contadorAdmin = 0;                                                                                  // CAMBIADO HASTA AQUI 

class Dueno : public Persona, public Usuario {
	private:
	    string cedula;
	    string direccion;
	    static int contadorDuenos;
	    vector <Mascota*> mascotas;
	
		//Generador de ID	
	    static string generarIdSistema () {
	        stringstream ss;
	        ss << "DUE" << setfill('0') << setw(3) << ++contadorDuenos;
	        return ss.str();
	    }
	public:
		//Constructor
	    Dueno (const string& nombre, const string& telefono, const string& email, const string& contrasena, const string& cedula, const string& direccion) : 
		Persona (nombre, telefono, email), Usuario (generarIdSistema(), contrasena, "Dueno"), direccion (direccion), cedula (cedula) {}
		
		//Getters
	    string getDireccion () const { 
			return direccion; 
		}
		string getCedula () const {
			return cedula;
		}
		
		//Setters
	    void setDireccion (const string& n_direccion) { 
			direccion = n_direccion; 
		}
		void setCedula (const string& n_cedula) {
			cedula = n_cedula;
		}
		
		//Metodos
	    void mostrarInfo () const override {
	        cout << "ID: " << idSistema << ", Nombre: " << nombre << ", Telefono: " << telefono << ", Email: " << email << ", Cedula" << cedula << ", Direccion: " << 
			direccion << endl;
	    }
	    
	    //Destructor
	    ~Dueno () {}
};

int Dueno::contadorDuenos = 0;

class Veterinario : public Persona, public Usuario {
	private:
	    string especialidad;
	    vector <Cita*> citasAsignadas;
	    static int contadorVeterinarios;
	    
	    //Generador de ID
	    static string generarIdSistema () {
	        stringstream ss;
	        ss << "VET" << setfill('0') << setw(3) << ++contadorVeterinarios;
	        return ss.str();
	    }
	public:
		//Constructor
	    Veterinario (const string& nombre, const string& telefono, const string& email, const string& contrasena, const string& especialidad): Persona (nombre, telefono, email),
	    Usuario (generarIdSistema (), contrasena, "Veterinario"), especialidad (especialidad) {}
		
		//Getters
	    string getEspecialidad () const { 
			return especialidad; 
		}

		//Setters
	    void setEspecialidad (const string& n_especialidad) { 
			especialidad = n_especialidad; 
		}
	    
	    //Metodos
	    void agregarCita (Cita* cita);
	    void eliminarCita (const string& idCita);
	    void mostrarCitasAsignadas () const;
	
	    void mostrarInfo() const override {
	        cout << "ID: " << idSistema << ", Nombre: " << nombre << ", Especialidad: " << especialidad << ", Telefono: " << telefono << ", Email: " << email << endl;
	    }
	    
	    //Destructor
	    ~Veterinario () {}
};

int Veterinario::contadorVeterinarios = 0;

class Recepcionista : public Persona, public Usuario {
	private:
	    string turno;
	    static int contadorRecepcionistas;
	
		//Generador de ID
	    static string generarIdSistema () {
	        stringstream ss;
	        ss << "REP" << setfill('0') << setw(3) << ++contadorRecepcionistas;
	        return ss.str();
	    }
	public:
		//Constructor
	    Recepcionista (const string& nombre, const string& telefono, const string& email, const string& contrasena, const string& turno) : Persona(nombre, telefono, email),
	    Usuario(generarIdSistema(), contrasena, "Recepcionista"), turno(turno) {}
	    
	    //Getters
	    string getTurno () const {
	    	return turno;
		}
		
		//Setters
		void setTurno (string n_turno) {
			turno = n_turno;
		}
		
		//Metodos
	    void mostrarInfo () const override {
	        cout << "ID: " << idSistema << ", Nombre: " << nombre << ", Turno: " << turno << ", Telefono: " << telefono << ", Email: " << email << endl;
	    }
	    
	    //Destructor
	    ~Recepcionista () {}
};

int Recepcionista::contadorRecepcionistas = 0;

class HistorialMedico {
	private:
		double peso;
		double altura;
	    vector <string> entradas;
	
	public:
		//Getters
		double getPeso () const {
			return peso;
		}
		double getAltura () const {
			return altura;
		}
		
		//Setters
		void setPeso (double n_peso) {
			peso = n_peso;
		}
		void setAltura (double n_altura) {
			altura = n_altura;
		}
		
		//Metodos
	    void agregarEntrada (const string& entrada) {
	    	double n_peso;
	    	double n_altura;
	    	cout << "Ingrese el peso: ";
	    	cin >> n_peso;
	    	setPeso (n_peso);
	    	cout << "Ingrese la altura: ";
	    	cin >> n_altura;
	    	setAltura (n_altura);
	    	cin.ignore ();
	        entradas.push_back(entrada);
	    }
	
	    void mostrarHistorial () const {
	        if (entradas.empty()) {
	            cout << "No hay registros en el historial medico." << endl;
	            return;
	        }
	        cout << endl << "Historial medico:" << endl;
	        cout << "Altura: " << altura << "cm" << endl;
	        cout << "Peso: " << peso << "kg" << endl;
	        int numero = 1;
	        for (auto &entrada : entradas) {
	            cout << numero << ". " << entrada << endl;
	            numero++;
	        }
	    }
};

class Mascota {
	private:
	    string idMascota;
	    string nombre;
	    string especie;
	    string raza;
	    int edad;
	    Dueno* propietario;
	    HistorialMedico historialMedico;
	    static int contadorMascotas;
	
		//Generador de ID
	    static string generarIdMascota () {
	        stringstream ss;
	        ss << "MAS" << setfill('0') << setw(3) << ++contadorMascotas;
	        return ss.str();
	    }
	public:
		//Constructor
	    Mascota (const string& nombre, const string& especie, const string& raza, int edad, Dueno* propietario): idMascota (generarIdMascota()), nombre (nombre), especie (especie), 
		raza (raza), edad (edad), propietario (propietario) {}
	    Mascota (const string& nombre, int edad, Dueno* propietario) : idMascota (generarIdMascota()), nombre (nombre), especie ("No especificada"), raza ("No especificada"),
	    edad(edad), propietario(propietario) {}
	    
		//Getters
	    string getIdMascota () const { 
			return idMascota; 
		}
	    string getNombre () const { 
			return nombre; 
		}
	    string getEspecie () const { 
			return especie; 
		}
	    string getRaza () const { 
			return raza; 
		}
	    int getEdad () const { 
			return edad; 
		}
	    Dueno* getPropietario () const {
			return propietario; 
		}
	    
		//Setters
	    void setNombre (const string& n_nombre) { 
			nombre = n_nombre; 
		}
	    void setEspecie (const string& n_especie) { 
			especie = n_especie; 
		}
	    void setRaza (const string& n_raza) { 
			raza = n_raza; 
			}
	    void setEdad (int n_edad) { 
			edad = n_edad; 
		}
	    void setPropietario (Dueno* n_propietario) { 
			propietario = n_propietario; 
		}
		
		//Metodos
	    void agregarAlHistorial (const string& entrada) {
	        historialMedico.agregarEntrada (entrada);
	    }
	    void mostrarHistorial () const {
	        historialMedico.mostrarHistorial ();
	    }
	    void mostrarInfo () const {
	        cout << "ID: " << idMascota << ", Nombre: " << nombre << ", Especie: " << especie << ", Raza: " << raza << ", Edad: " << edad;
	        if (propietario != 0) {
	            cout << ", Dueno: " << propietario -> getNombre() << " (" << propietario ->getIdSistema() << ")";
	        }
	        cout << endl;
	    }
};

int Mascota :: contadorMascotas = 0;

class Servicio {
	protected:
	    string idServicio;
	    string nombre;
	    string descripcion;
	    double precioBase;
	    int duracionMinutos;
	    static int contadorServicios;
		
		//Generador de ID
	    static string generarIdServicio() {
	        stringstream ss;
	        ss << "SER" << setfill('0') << setw(3) << ++contadorServicios;
	        return ss.str();
	    }
	
	public:
		//Constructor
	    Servicio(const string& nombre, const string& descripcion, double precioBase, int duracionMinutos) : idServicio(generarIdServicio()), nombre(nombre), descripcion(descripcion),
	    precioBase(precioBase), duracionMinutos(duracionMinutos) {}
	
		//Getters
	    string getIdServicio () const { 
			return idServicio; 
		}
	    string getNombre () const { 
			return nombre; 
		}
		string getDescripcion () const {
			return descripcion;
		}
		double getprecioBase () const {
			return precioBase;
		}
	    int getDuracionMinutos() const { 
			return duracionMinutos; 
		}
		
		//Setters
		void setNombre (string n_nombre) {
			nombre = n_nombre;
		}
		void setDescripcion (string n_descripcion) {
			descripcion = n_descripcion;
		}
		void setPrecioBase (double n_precio) {
			precioBase = n_precio;
		}
		void setDuracionMinutos (int n_duracion) {
			duracionMinutos = n_duracion;
		}
		
		//Metodos
	    template <typename T>
	    double calcularPrecio (T impuesto) const {
	        return precioBase * (1.0 + (impuesto)/100) + getRecargo ();
	    }
	
		//Metodos Virtuales Puros
	    virtual double getRecargo () const = 0;
	    virtual void mostrarInfo () const = 0;
	    virtual string procesarServicio () = 0;
	    
	    //Destructor
	    virtual ~Servicio() {}
};

int Servicio::contadorServicios = 0;

class ServicioMedico : public Servicio {
	private:
	    bool requiereDiagnostico;
	    vector <string> medicamentos;
	public:
		//Contructor
	    ServicioMedico (const string& nombre, const string& descripcion, double precioBase, int duracionMinutos, bool requiereDiagnostico) : Servicio (nombre, descripcion, 
		precioBase, duracionMinutos), requiereDiagnostico (requiereDiagnostico) {}
		
		//Getters
		bool getRequiereDiagnostico () const {
			return requiereDiagnostico;
		}
		
		//Setters
		void setRequiereDiagnostico (bool n_requiere) {
			requiereDiagnostico = n_requiere;
		}
		
		//Metodos
	    void agregarMedicamento (const string& medicamento) {
	        medicamentos.push_back(medicamento);
	        cout << "Medicamento agregado correctamente." << endl;
	    }
	    void eliminarMedicamento (const string& medicamento) {
	    	for (auto it = medicamentos.begin(); it != medicamentos.end(); ++it) {
				if (*it == medicamento) {
				    medicamentos.erase(it);
				    cout << "El medicamento se ha eliminado correctamente." << endl;
				    return;
				}
			}
			cout << "Medicamento no encontrado." << endl;
		}
		void mostrarMedicamentos () const {
			for (const auto& medicamento : medicamentos) {
				cout << medicamento << endl;
			}
		}
	    double getRecargo () const override {
	        if (requiereDiagnostico) {
	        	return 7.5;
			}
			else {
				return 0;
			}
	    }
	    string procesarServicio() override {
		    string diagnostico;
		    int opcion;
		
			do {
			    cout << "1. Requiere diagnostico" << endl;
			    cout << "2. No requiere diagnostico" << endl;
			
			    cout << "Seleccione una opcion: ";
			    cin >> opcion;
			    if (cin.fail ()) {
			    	cin.clear ();
			    	cin.ignore (1000, '\n');
			    	opcion = 0;
			    	cout << "Opcion no valida." << endl;
			    	continue;
				}
				cin.ignore ();
			    
			    if (opcion == 1) {
			    	setRequiereDiagnostico (true);
			    	cout << "Diagnostico u observaciones: ";
			    	getline (cin, diagnostico);
			    	string medicamento;
			        cout << "Medicamento utilizado: ";
			        getline (cin, medicamento);
			        agregarMedicamento(medicamento);
			        diagnostico += " / Medicamento: " + medicamento;
			        return diagnostico;	
				}
				else if (opcion == 2) {
					setRequiereDiagnostico (false);
					cout << "Observaciones: ";
			    	getline (cin, diagnostico);
			    	string medicamento;
			        cout << "Medicamento utilizado: ";
			        getline (cin, medicamento);
			        agregarMedicamento (medicamento);
			        diagnostico += " / Medicamento: " + medicamento;
			        return diagnostico;
				}
				else {
					cout << "Opcion no valida." << endl;
				}
			}
			while (opcion != 1 and opcion != 2);
			return "";
		}
	    void mostrarInfo () const override {
	        cout << "Servicio medico - ID: " << idServicio << ", Nombre: " << nombre << ", Precio final (12%): $" << fixed << setprecision(2) << calcularPrecio(12) << endl;
	    }
	    //Destructor
	    ~ServicioMedico () {}
};

class ServicioEstetico : public Servicio {
	private:
	    string tipoEstetica;
	    vector <string> productos;
	public:
		//Constructor
	    ServicioEstetico (const string& nombre, const string& descripcion, double precioBase, int duracionMinutos, const string& tipoEstetica) : Servicio(nombre, 
		descripcion, precioBase, duracionMinutos), tipoEstetica (tipoEstetica) {}
		
		//Getters
		string getTipoEstetica () {
			return tipoEstetica;
		}
		
		//Setters
		void setTipoEstetica (string n_tipo) {
			tipoEstetica = n_tipo;
		}
		
		//Metodos
	    void agregarProducto(const string& producto) {
	        productos.push_back(producto);
	        cout << "Producto agregado correctamente." << endl;
	    }
	    void eliminarProducto (const string& producto) {
	    	for (auto it = productos.begin(); it != productos.end(); ++it) {
				if (*it == producto) {
				    productos.erase(it);
				    cout << "El producto se ha eliminado correctamente." << endl;
				    return;
				}
			}
			cout << "Producto no encontrado." << endl;
		}
	    double getRecargo() const override {
	        if (productos.size () >= 8) {
				return 7;
			}
			else if (productos.size () >= 5) {
				return 5;
			}
			else if (productos.size () >= 3) {
	        	return 3;
			}
			else {
				return 0;
			}
	    }
	    string procesarServicio() override {
		    string diagnostico = "Servicio estetico realizado";
		    int cantidadProductos;
		    while (true) {
		    	cout << "Cantidad de productos usados: ";
		    	cin >> cantidadProductos;
		    	if (cin.fail () or cantidadProductos < 0) {
		    		cin.clear ();
		    		cin.ignore (1000, '\n');
		    		cout << "Cantidad invalida." << endl;
				}
				else {
					cin.ignore ();
					break;
				}
			}
		    for (int i = 0; i < cantidadProductos; i++) {
		        string producto;
		        cout << "Producto " << i + 1 << ": ";
		        getline(cin, producto);
		        agregarProducto(producto);
		        diagnostico += " / Producto: " + producto;
		    }

    		return diagnostico;
		}
	    void mostrarInfo() const override {
	        cout << "Servicio estetico - ID: " << idServicio << ", Nombre: " << nombre << ", Precio final (15%): $" << fixed << setprecision(2) << calcularPrecio(15) << endl;;
	    }
	    //Destructor
	    ~ServicioEstetico () {}
};

template <typename T>
class GestorServicios {
	private:
	    vector <T*> servicios;
	public:
		//Metodos CRUD
	    void agregarServicio (T* servicio) {
	        servicios.push_back(servicio);
	    }
	    void listarServicios () const {
	        if (servicios.empty()) {
	            cout << "No hay servicios registrados." << endl;
	            return;
	        }
	        for (const auto& servicio : servicios) {
	            servicio -> mostrarInfo ();
	        }
	    }
	    
	        void buscarServicioPorID (const string& id) const {
            for (const auto& s : servicios) {
	            if (s -> getIdServicio() == id) {
		            s -> mostrarInfo();
		            return;
        		}
    		}
   			cout << "Servicio no encontrado." << endl;
		}
        void buscarServicioPorNombre(const string& nombre) const {
            bool encontrado = false;
            for (const auto& s : servicios) {
        		if (s -> getNombre () == nombre) {
		            s -> mostrarInfo ();
		            encontrado = true;
        		}
    		}
    		if (!encontrado) cout << "Servicio no encontrado." << endl;
		}
        void editarServicio(const string& id) {
        	for (auto& s : servicios) {
            	if (s -> getIdServicio () == id) {
		            string nombre, descripcion;
		            double precio;
		            int duracion;
		
		            cout << "Nuevo nombre: ";
		            getline (cin, nombre);
		            cout << "Nueva descripcion: ";
		            getline (cin, descripcion);
		            cout << "Nuevo precio: ";
		            cin >> precio;
		            cout << "Nueva duracion: ";
		            cin >> duracion;
		            cin.ignore();
		
		            s -> setNombre (nombre);
		            s -> setDescripcion (descripcion);
		            s -> setPrecioBase (precio);
		            s -> setDuracionMinutos (duracion);
		
		            cout << "Servicio actualizado." << endl;
		            return;
        		}
    		}
    		cout << "Servicio no encontrado." << endl;
		}
        void eliminarServicio(const string& id) {
        	for (auto it = servicios.begin(); it != servicios.end(); ++it) {
		        if ((*it) -> getIdServicio() == id) {
		            delete *it;
		            servicios.erase(it);
		            cout << "Servicio eliminado." << endl;
		            return;
		        }
    		}
    		cout << "Servicio no encontrado." << endl;
		}                                                                            
	    
	     //Getters
	    T* getServicio (const string& idServicio) const {
	        for (const auto& servicio : servicios) {
	            if (servicio -> getIdServicio() == idServicio) {
	                return servicio;
	            }
	        }
	        return NULL;
	    }
	    //Destructor
	    ~GestorServicios() {
	        for (auto servicio : servicios) {
	            delete servicio;
	        }
	    }
};

class Cita {
	private:
	    string idCita;
	    string fecha;
	    string hora;
	    Servicio* servicioSolicitado;
	    Veterinario* veterinarioAsignado;
	    Mascota* mascotaAtendida;
	    string diagnostico;
	    bool completada;
	    static int contadorCitas;
	
		//Generador de ID
	    static string generarIdCita () {
	        stringstream ss;
	        ss << "CIT" << setfill('0') << setw(3) << ++contadorCitas;
	        return ss.str();
	    }
	public:
		//Constructor
	    Cita (const string& fecha, const string& hora, Servicio* servicioSolicitado, Veterinario* veterinarioAsignado, Mascota* mascotaAtendida): idCita (generarIdCita()),
	    fecha (fecha), hora (hora), servicioSolicitado (servicioSolicitado), veterinarioAsignado (veterinarioAsignado), mascotaAtendida (mascotaAtendida), diagnostico ("Pendiente"), 
		completada (false) {}
	
		//Getters
	    string getIdCita () const { 
			return idCita;
		}
	    string getFecha () const { 
			return fecha; 
		}
	    string getHora () const { 
			return hora; 
		}
	    Servicio* getServicioSolicitado () const { 
			return servicioSolicitado; 
		}
	    Veterinario* getVeterinarioAsignado () const { 
			return veterinarioAsignado; 
		}
	    Mascota* getMascotaAtendida () const { 
			return mascotaAtendida; 
		}
	    bool isCompletada () const { 
			return completada; 
		}
	
		//Setters
	    void setFecha (const string& n_fecha) { 
			fecha = n_fecha; 
		}
	    void setHora (const string& n_hora) { 
			hora = n_hora; 
		}
	    void setServicioSolicitado (Servicio* n_servicio) { 
			servicioSolicitado = n_servicio; 
		}
	    void setVeterinarioAsignado (Veterinario* n_veterinario) { 
			veterinarioAsignado = n_veterinario; 
		}
	    void setMascotaAtendida (Mascota* n_mascota) { 
			mascotaAtendida = n_mascota; 
		}
		
		//Metodos
	    void completarCita (const string& nuevoDiagnostico) {
	        diagnostico = nuevoDiagnostico;
	        completada = true;
	        if (mascotaAtendida != 0) {
	            mascotaAtendida -> agregarAlHistorial ("Consulta " + fecha + " " + hora + ": " + diagnostico);
	        }
	    }
	    void mostrarInfo () const {
	        cout << "ID: " << idCita << ", Fecha: " << fecha << ", Hora: " << hora<< ", Veterinario: " << veterinarioAsignado ->getNombre () << ", Mascota: " << 
			mascotaAtendida -> getNombre () << ", Servicio: " << servicioSolicitado -> getNombre() << ", Estado: " << (completada ? "Completada" : "Pendiente") << endl;
	    }
};

int Cita::contadorCitas = 0;

void Veterinario :: agregarCita (Cita* cita) {
	citasAsignadas.push_back (cita);
}

void Veterinario :: eliminarCita (const string& idCita) {
	for (auto it = citasAsignadas.begin(); it != citasAsignadas.end(); ++it) {
		if ((*it) -> getIdCita () == idCita) {
			citasAsignadas.erase (it);
			return;
		}
	}
}

void Veterinario :: mostrarCitasAsignadas () const {
	if (citasAsignadas.empty ()) {
		cout << "No hay citas asignadas." << endl;
		return;
	}
	for (const auto& cita : citasAsignadas) {
		cita -> mostrarInfo ();
	}
}

	class GestorDuenos {
	private:
	    vector <Dueno*> duenos;
	public:
		//Metodos CRUD
	    void agregarDueno (Dueno* dueno) {
	        duenos.push_back(dueno);
	    }
	    void listarDuenos () const {
	        if (duenos.empty()) {
	            cout << "No hay duenos registrados." << endl;
	            return;
	        }
	        for (const auto& dueno : duenos) {
	            dueno -> mostrarInfo();
	        }
	    }
        void buscarDuenoPorID (const string& id) const {
            for (const auto& dueno : duenos) {
	            if (dueno -> getIdSistema () == id) {
	            	dueno -> mostrarInfo ();
	            return;
            	}
       		}
          cout << "Dueno no encontrado." << endl;
       	}

        void buscarDuenoPorNombre (const string& nombre) const {
        	bool encontrado = false;
        	for (const auto& dueno : duenos) {
        		if (dueno -> getNombre () == nombre) {
            		dueno -> mostrarInfo ();
            		encontrado = true;
        		}
       		}
       		if (!encontrado) cout << "Dueno no encontrado." << endl;
      	}

        void editarDueno (const string& id) {
         	for (auto& dueno : duenos) {
        		if (dueno -> getIdSistema () == id) {
	            string nombre, telefono, email, direccion;
	            cout << "Nuevo nombre: ";
	            getline(cin, nombre);
	            cout << "Nuevo telefono: ";
	            getline(cin, telefono);
	            cout << "Nuevo email: ";
	            getline(cin, email);
	            cout << "Nueva direccion: ";
	            getline(cin, direccion);
	
	            dueno -> setNombre (nombre);
	            dueno -> setTelefono (telefono);
	            dueno -> setEmail (email);
	            dueno -> setDireccion (direccion);
	
	            cout << "Dueno actualizado." << endl;
	            return;
        		}	
      		}
         	cout << "Dueno no encontrado." << endl;
        }

        void eliminarDueno (const string& id) {
          	for (auto it = duenos.begin(); it != duenos.end(); ++it) {
        		if ((*it) -> getIdSistema () == id) {
            		delete *it;
            		duenos.erase(it);
            		cout << "Dueno eliminado." << endl;
           			return;
        		}
    		}
    		cout << "Dueno no encontrado." << endl;
		}
		
	    //Getters
	    const vector <Dueno*>& getDuenos () const {
	        return duenos;
	    }
	    Dueno* getDueno (const string& idSistema) const {
	        for (auto dueno : duenos) {
	            if (dueno -> getIdSistema () == idSistema) {
	                return dueno;
	            }
	        }
	        return NULL;
	    }
	    
	    //Destructor
	    ~GestorDuenos () {
	        for (auto dueno : duenos) {
	            delete dueno;
	        }
	    }
};

class GestorMascotas {
	private:
	    vector <Mascota*> mascotas;
	public:
		//Metodos CRUD
	    void agregarMascota (Mascota* mascota) {
	        mascotas.push_back(mascota);
	    }
	    void buscarMascota (const string& idMascota) const {
	        for (const auto& mascota : mascotas) {
	            if (mascota -> getIdMascota () == idMascota) {
	                mascota -> mostrarInfo ();
	                return;
	            }
	        }
	        cout  << "Mascota no encontranda." << endl;
	    }
	    void editarMascota (const string& idMascota) {
	        for (auto& mascota : mascotas) {	
		        if (mascota -> getIdMascota () == idMascota) {
		        string nombre;
		        string especie;
		        string raza;
		        int edad;
		
		        cout << "Nuevo nombre: ";
		        getline (cin, nombre);
		        cout << "Nueva especie: ";
		        getline (cin, especie);
		        cout << "Nueva raza: ";
		        getline (cin, raza);
		        cout << "Nueva edad: ";
		        cin >> edad;
		        cin.ignore();
	
		        mascota -> setNombre (nombre);
		        mascota -> setEspecie (especie);
		        mascota -> setRaza (raza);
		        mascota -> setEdad (edad);
		        cout << "Mascota actualizada correctamente." << endl;
		        return;
		        }
	    	}
	    	cout << "Mascota no encontranda." << endl;
	    }
	    void eliminarMascota (const string& idMascota) {
	        for (auto it = mascotas.begin(); it != mascotas.end(); ++it) {
	            if ((*it) -> getIdMascota () == idMascota) {
	                delete *it;
	                mascotas.erase(it);
	                cout << "Mascota eliminada correctamente." << endl;
	                return;
	            }
	        }
	        cout << "Mascota no encontranda." << endl;
	    }
	    void listarMascotas () const {
	        if (mascotas.empty()) {
	            cout << "No hay mascotas registradas." << endl;
	            return;
	        }
	        for (const auto& mascota : mascotas) {
	            mascota -> mostrarInfo();
	        }
	    }
	    void listarMascotasDeDueno (const string& idDueno) const {
        bool encontrada = false;
        for (const auto& mascota : mascotas) {
            if (mascota -> getPropietario () != NULL and mascota -> getPropietario () -> getIdSistema () == idDueno) {
                mascota -> mostrarInfo();
                encontrada = true;
            }
        }

        if (encontrada == false) {
            cout << "No hay mascotas para este dueno." << endl;
        }
    }
	    void buscarMascotaPorNombre (const string& nombreMascota) const {
	        bool encontrada = false;
	        for (const auto& mascota : mascotas) {
	            if (mascota -> getNombre () == nombreMascota) {
	                mascota -> mostrarInfo ();
	                encontrada = true;
	            }
	        }
	        if (encontrada == false) {
	            cout << "Mascota no encontranda." << endl;
	        }
	    }
		//Getters
		Mascota* getMascota (const string& idMascota) const {
        for (auto mascota : mascotas) {
            if (mascota -> getIdMascota () == idMascota) {
                return mascota;
            }
        }
        return NULL;
    }
	    Mascota* getMascotaPorNombre (const string& nombreMascota, const string& idDueno = "") const {
	        for (auto mascota : mascotas) {
	            if (mascota -> getNombre () == nombreMascota) {
	                if (idDueno == "" or mascota -> getPropietario () == NULL or mascota -> getPropietario () -> getIdSistema () == idDueno) {
	                    return mascota;
	                }
	            }
	        }
	        return NULL;
	    }
		
		//Destructor
	    ~GestorMascotas() {
	        for (auto mascota : mascotas) {
	            delete mascota;
	        }
    }
};

class GestorVeterinarios {
	private:
	    vector <Veterinario*> veterinarios;
	public:
		//Metodos CRUD
	    void agregarVeterinario (Veterinario* veterinario) {
	        veterinarios.push_back(veterinario);
	    }
	    void buscarVeterinario (const string& idSistema) const {
	        for (const auto& veterinario : veterinarios) {
	            if (veterinario -> getIdSistema() == idSistema) {
	                veterinario -> mostrarInfo ();
	                return;
	            }
	        }
	        cout << "Veterinario no encontrando." << endl;
	    }
	    void editarVeterinario (const string& idSistema) {
	        for (const auto& veterinario : veterinarios) {
	        	if (veterinario -> getIdSistema() == idSistema) {
	                string nombre;
			        string telefono;
			        string email;
			        string especialidad;
			
			        cout << "Nuevo nombre: ";
			        getline (cin, nombre);
			        cout << "Nuevo telefono: ";
			        getline (cin, telefono);
			        cout << "Nuevo email: ";
			        getline (cin, email);
			        cout << "Nueva especialidad: ";
			        getline (cin, especialidad);
			
			        veterinario -> setNombre (nombre);
			        veterinario -> setTelefono (telefono);
			        veterinario -> setEmail (email);
			        veterinario -> setEspecialidad (especialidad);
			        cout << "Veterinario actualizado correctamente." << endl;
			        return;
	            }  
	        }
			cout << "Veterinario no encontrando." << endl;
	    }
	    void eliminarVeterinario (const string& idVeterinario) {
	        for (auto it = veterinarios.begin(); it != veterinarios.end(); ++it) {
	            if ((*it) -> getIdSistema () == idVeterinario) {
	                delete *it;
	                veterinarios.erase(it);
	                cout << "Veterinario eliminado correctamente." << endl;
	                return;
	            }
	        }
	        cout << "Veterinario no encontrando." << endl;
	    }
	    void listarVeterinarios () const {
	        if (veterinarios.empty()) {
	            cout << "No hay veterinarios registrados." << endl;
	            return;
	        }
	        for (const auto& veterinario : veterinarios) {
	            veterinario -> mostrarInfo();
	        }
	    }
	    
	    void listarPorEspecialidad (const string& especialidad) const {
	    	bool encontrado = false;
	        for (const auto& veterinario : veterinarios) {
	            if (veterinario -> getEspecialidad () == especialidad) {
	                veterinario -> mostrarInfo ();
	                encontrado = true;
	            }
	        }
	        if (encontrado == false) {
	        	cout << "No hay veterinarios con esa especialidad" << endl;
			}
	    }
	    
	    //Getters
	    const vector<Veterinario*>& getVeterinarios() const {
	        return veterinarios;
	    }
	    Veterinario* getVeterinario (const string& idSistema) const {
	        for (const auto& veterinario : veterinarios) {
	            if (veterinario -> getIdSistema () == idSistema) {
	                return veterinario;
	            }
	        }
	        return NULL;
		}
		//Destructor
	    ~GestorVeterinarios() {
	        for (auto veterinario : veterinarios) {
	            delete veterinario;
	        }
	    }
};

class GestorCitas {
	private:
	    vector <Cita*> citas;
	public:
	    bool hayConflicto (const string& fecha, const string& hora, Veterinario* veterinario, Mascota* mascota) const {
	        for (const auto& cita : citas) {
	            if (cita -> getFecha() == fecha and cita -> getHora() == hora) {
	                if (cita -> getVeterinarioAsignado() == veterinario or cita -> getMascotaAtendida() == mascota) {
	                    return true;
	                }
	            }
	        }
	        return false;
	    }
	    //Metodos CRUD
	    void agregarCita (Cita* cita) {
	        if (hayConflicto(cita -> getFecha (), cita -> getHora (), cita -> getVeterinarioAsignado (), cita -> getMascotaAtendida ())) {
	            cout << "Conflicto de horario. No se pudo registrar la cita." << endl;
	            delete cita;
	            return;
	        }
	        citas.push_back(cita);
	        cout << "Cita registrada correctamente." << endl;
	    }
	    void buscarCita (const string& idCita) const {
	        for (const auto& cita : citas) {
	            if (cita -> getIdCita() == idCita) {
	                cita -> mostrarInfo();
	                return;
	            }
	        }
	        cout << "Cita no encontrada" << endl;
	    }
	    void eliminarCita (const string& idCita) {
	        for (auto it = citas.begin(); it != citas.end(); ++it) {
	            if ((*it) -> getIdCita () == idCita) {
	                delete *it;
	                citas.erase(it);
	                cout << "Cita eliminada correctamente." << endl;
	                return;
	            }
	        }
	        cout << "Cita no encontrada." << endl;
	    }
	    void reprogramarCita (const string& idCita, const string& fecha, const string& hora) {
		    for (const auto& cita : citas) {
		        if (cita -> getIdCita () == idCita) {
		
		            for (const auto& otraCita : citas) {
		                if (otraCita -> getIdCita () != idCita) {
		                    if (otraCita -> getFecha() == fecha and otraCita -> getHora() == hora) {
		                        if (otraCita -> getVeterinarioAsignado () == cita -> getVeterinarioAsignado() or otraCita -> getMascotaAtendida () == cita -> getMascotaAtendida ()) {
		                            cout << "Conflicto de horario. No se puede reprogramar la cita." << endl;
		                            return;
		                        }
		                    }
		                }
		            }
		
		            cita -> setFecha (fecha);
		            cita -> setHora (hora);
		            cout << "Cita reprogramada correctamente." << endl;
		            return;
		        }
		    }
		
		    cout << "Cita no encontrada." << endl;
		}
	    void listarCitas() const {
	        if (citas.empty()) {
	            cout << "No hay citas registradas." << endl;;
	            return;
	        }
	        for (const auto& cita : citas) {
	            cita -> mostrarInfo ();
	        }
	    }
	
	    void listarCitasPorFecha (const string& fecha) const {
	        bool encontrada = false;
	        for (const auto& cita : citas) {
	            if (cita -> getFecha () == fecha) {
	                cita -> mostrarInfo ();
	                encontrada = true;
	            }
	        }
	        if (encontrada == false) {
	            cout << "No hay citas para esa fecha." << endl;
	        }
    }

    void listarAgendaVeterinario (const string& idVeterinario, const string& fecha) const {
        bool encontrada = false;
        for (auto cita : citas) {
            if (cita -> getVeterinarioAsignado () -> getIdSistema () == idVeterinario and
                cita -> getFecha () == fecha) {
                cita -> mostrarInfo ();
                encontrada = true;
            }
        }

        if (encontrada == false) {
            cout << "No hay citas para este veterinario en esa fecha." << endl;
        }
    }

    void listarCitasPorDueno (const string& nombre_dueno) const {
        bool encontrada = false;
        for (const auto& cita : citas) {
            if (cita -> getMascotaAtendida () -> getPropietario () -> getNombre () == nombre_dueno) {
                cita -> mostrarInfo ();
                encontrada = true;
            }
        }
        if (encontrada == false) {
            cout << "No hay citas registradas para este dueno." << endl;
        }
    }
    Cita* getCita (const string& idCita) const {
    	for (const auto& cita : citas) {
    		if (cita -> getIdCita () == idCita) {
    			return cita;
			}
		}
		return NULL;
	}

    ~GestorCitas() {
        for (auto& cita : citas) {
            delete cita;
        }
    }
};

class SistemaVeterinaria {
	private:
	    GestorDuenos gestorDuenos;
	    GestorVeterinarios gestorVeterinarios;
	    GestorMascotas gestorMascotas;
	    GestorCitas gestorCitas;
	    GestorServicios <ServicioMedico> gestorServiciosMedicos;
	    GestorServicios <ServicioEstetico> gestorServiciosEsteticos;
	    vector <Recepcionista*> recepcionistas;
	    vector<Administrador*> administradores;                                                                               // AGREGADO                             
	    Usuario* usuarioActual;
	    
		//Metodos
	    bool esBisiesto (int anio) const {
	        return (anio % 400 == 0) or (anio % 4 == 0 and anio % 100 != 0);
	    }
	    void validarFecha (int dia, int mes, int anio) {
	        if (anio < 0) {
	            throw invalid_argument ("Fecha invalida.");
	        }
	        if (mes < 1 or mes > 12) {
	            throw invalid_argument ("Fecha invalida.");
	        }
	        int diasMes [] = {31,28,31,30,31,30,31,31,30,31,30,31};
	        if (esBisiesto (anio)) {
	            diasMes [1] = 29;
	        }
	        if (dia < 1 or dia > diasMes [mes - 1]) {
	            throw invalid_argument ("Fecha invalida.");
	        }
	    }
	    void validarHora (int horas, int minutos) {
	        if (horas < 0 or horas > 23 or minutos < 0 or minutos > 59) {
	            throw invalid_argument ("Hora invalida.");
	        }
	    }
	    void validarTurno (int horaIngreso, int minutosIngreso, int horaSalida, int minutosSalida) {
	        validarHora (horaIngreso, minutosIngreso);
	        validarHora (horaSalida, minutosSalida);
	        if (horaSalida < horaIngreso or (horaSalida == horaIngreso and minutosSalida <= minutosIngreso)) {
	            throw invalid_argument ("Turno invalido.");
	        }
	    }
	    void validarEdad (int edad) {
	        if (edad < 0) {
	            throw invalid_argument ("Edad invalida.");
	        }
	    }
	    int leerEntero (const string& mensaje) {
	        int numero;
	        while (true) {
	            try {
	                cout << mensaje;
	                cin >> numero;
	                if (cin.fail ()) {
	                    throw invalid_argument ("Opcion invalida.");
	                }
	                cin.ignore ();
	                return numero;
	            }
	            catch (const exception& e) {
	                cout << e.what () << endl;
	                cin.clear ();
	                cin.ignore (1000, '\n');
	            }
	        }
	    }
	    int leerEdadValida (const string& mensaje) {
	        int edad;
	        while (true) {
	            try {
	                edad = leerEntero (mensaje);
	                validarEdad (edad);
	                return edad;
	            }
	            catch (const exception& e) {
	                cout << e.what () << endl;
	            }
	        }
	    }
	    string formatearDosDigitos (int numero) const {
	        stringstream ss;
	        ss << setfill ('0') << setw (2) << numero;
	        return ss.str ();
	    }
	    string leerFechaValida () {
	        int dia;
	        int mes;
	        int anio;
	        while (true) {
	            try {
	                dia = leerEntero ("Dia: ");
	                mes = leerEntero ("Mes: ");
	                anio = leerEntero ("Anio: ");
	                validarFecha (dia, mes, anio);
	                return formatearDosDigitos (dia) + "/" + formatearDosDigitos (mes) + "/" + to_string (anio);
	            }
	            catch (const exception& e) {
	                cout << e.what () << endl;
	            }
	        }
	    }
	    string leerHoraValida () {
	        int horas;
	        int minutos;
	        while (true) {
	            try {
	                horas = leerEntero ("Horas: ");
	                minutos = leerEntero ("Minutos: ");
	                validarHora (horas, minutos);
	                return formatearDosDigitos (horas) + ":" + formatearDosDigitos (minutos);
	            }
	            catch (const exception& e) {
	                cout << e.what () << endl;
	            }
	        }
	    }
	    string leerTurnoValido () {
	        int horaIngreso;
	        int minutosIngreso;
	        int horaSalida;
	        int minutosSalida;
	        while (true) {
	            try {
	                horaIngreso = leerEntero ("Hora de ingreso: ");
	                minutosIngreso = leerEntero ("Minutos de ingreso: ");
	                horaSalida = leerEntero ("Hora de salida: ");
	                minutosSalida = leerEntero ("Minutos de salida: ");
	                validarTurno (horaIngreso, minutosIngreso, horaSalida, minutosSalida);
	                return formatearDosDigitos (horaIngreso) + ":" + formatearDosDigitos (minutosIngreso) + " - " + formatearDosDigitos (horaSalida) + ":" + formatearDosDigitos (minutosSalida);
	            }
	            catch (const exception& e) {
	                cout << e.what () << endl;
	            }
	        }
	    }
	    Dueno* autenticarDueno (const string& id, const string& contrasena) const {
	    	const vector <Dueno*>& duenos = gestorDuenos.getDuenos ();
	        for (const auto& dueno : duenos) {
	            if (dueno -> getIdSistema () == id and dueno -> getContrasena () == contrasena) {
	                return dueno;
	            }
	        }
	        return NULL;
	    }
	    Veterinario* autenticarVeterinario (const string& id, const string& contrasena) const {
	        const vector <Veterinario*>& veterinarios = gestorVeterinarios.getVeterinarios ();
	        for (auto veterinario : veterinarios) {
	            if (veterinario -> getIdSistema () == id and veterinario -> getContrasena () == contrasena) {
	                return veterinario;
	            }
	        }
	        return NULL;
	    }
	    Recepcionista* autenticarRecepcionista (const string& id, const string& contrasena) const {
	        for (auto recepcionista : recepcionistas) {
	            if (recepcionista -> getIdSistema () == id and recepcionista -> getContrasena () == contrasena) {
	                return recepcionista;
	            }
	        }
	        return NULL;
	    }
	public:
	    //Constructor
		SistemaVeterinaria () : usuarioActual (NULL) {
	        Dueno* dueno = new Dueno ("Carlos Perez", "0991111111", "carlos@gmail.com", "due123", "1723456789", "Quito");
	        gestorDuenos.agregarDueno (dueno);
	        Veterinario* veterinario = new Veterinario ("Sofia Ruiz", "0982222222", "sofia@vet.com", "vet123", "General");
	        gestorVeterinarios.agregarVeterinario (veterinario);
	        Veterinario* veterinario2 = new Veterinario ("Daniel Torres", "0974444444", "daniel@vet.com", "vet234", "Cirugia");
	        gestorVeterinarios.agregarVeterinario (veterinario2);
	        Veterinario* veterinario3 = new Veterinario ("Maria Fernanda", "0965555555", "maria@vet.com", "vet345", "Dermatologia");
	        gestorVeterinarios.agregarVeterinario (veterinario3);
	        Veterinario* veterinario4 = new Veterinario ("Paula Rojas", "0956666666", "paula@vet.com", "vet456", "Estetica");
	        gestorVeterinarios.agregarVeterinario (veterinario4);
	        Recepcionista* recepcionista = new Recepcionista ("Ana Lopez", "0973333333", "ana@vet.com", "rep123", "08:00 - 17:00");
	        recepcionistas.push_back (recepcionista);
	        Mascota* mascota = new Mascota ("Max", "Perro", "Labrador", 5, dueno);
	        gestorMascotas.agregarMascota (mascota);
	        ServicioMedico* servicioMedico = new ServicioMedico ("Consulta general", "Revision basica", 25.0, 30, true);
	        gestorServiciosMedicos.agregarServicio (servicioMedico);
	        ServicioMedico* servicioMedico2 = new ServicioMedico ("Vacunacion", "Aplicacion de vacunas", 18.0, 20, false);
	        gestorServiciosMedicos.agregarServicio (servicioMedico2);
	        ServicioMedico* servicioMedico3 = new ServicioMedico ("Cirugia menor", "Procedimiento quirurgico basico", 90.0, 90, true);
	        gestorServiciosMedicos.agregarServicio (servicioMedico3);
	        ServicioMedico* servicioMedico4 = new ServicioMedico ("Revision dermatologica", "Control de piel y pelaje", 35.0, 40, true);
	        gestorServiciosMedicos.agregarServicio (servicioMedico4);
	        ServicioEstetico* servicioEstetico = new ServicioEstetico ("Bano y corte", "Aseo completo", 18.0, 45, "Higiene");
	        gestorServiciosEsteticos.agregarServicio (servicioEstetico);
	        ServicioEstetico* servicioEstetico2 = new ServicioEstetico ("Limpieza de oidos", "Higiene de oidos", 10.0, 15, "Higiene");
	        gestorServiciosEsteticos.agregarServicio (servicioEstetico2);
	        ServicioEstetico* servicioEstetico3 = new ServicioEstetico ("Corte de unas", "Mantenimiento de unas", 8.0, 10, "Belleza");
	        gestorServiciosEsteticos.agregarServicio (servicioEstetico3);
	        ServicioEstetico* servicioEstetico4 = new ServicioEstetico ("Spa canino", "Relajacion y cuidado especial", 30.0, 60, "Spa");
	        gestorServiciosEsteticos.agregarServicio (servicioEstetico4);
	        gestorCitas.agregarCita (new Cita ("26/04/2026", "10:30", servicioMedico, veterinario, mascota));
	    }
		
		//Metodos
	    bool iniciarSesion (const string& idSistema, const string& contrasena) {
	        Dueno* dueno = autenticarDueno (idSistema, contrasena);
	        if (dueno != NULL) {
	            usuarioActual = dueno;
	            return true;
	        }
	        Veterinario* veterinario = autenticarVeterinario (idSistema, contrasena);
	        if (veterinario != NULL) {
	            usuarioActual = veterinario;
	            return true;
	        }
	
	        Recepcionista* recepcionista = autenticarRecepcionista (idSistema, contrasena);
	        if (recepcionista != NULL) {
	            usuarioActual = recepcionista;
	            return true;
	        }
	        return false;
	    }
	    void cerrarSesion () {
	        usuarioActual = NULL;
	    }
	    
	   
	   
        void menuAdministrador() {                                             // CAMBIADO DESDE AQUI 
        int opcion;

       do {
        cout << endl;
        cout << "--- MENU ADMINISTRADOR ---" << endl;
        cout << "1. Registrar dueno" << endl;
        cout << "2. Editar dueno" << endl;
        cout << "3. Eliminar dueno" << endl;
        cout << "4. Buscar dueno por ID" << endl;
        cout << "5. Buscar dueno por nombre" << endl;
        cout << "6. Registrar veterinario" << endl;
        cout << "7. Listar veterinarios" << endl;
        cout << "8. Buscar veterinarios por especialidad" << endl;
        cout << "9. Actualizar veterinario" << endl;
        cout << "10. Eliminar veterinario" << endl;
        cout << "11. Registrar servicio" << endl;
        cout << "12. Editar servicio" << endl;
        cout << "13. Eliminar servicio" << endl;
        cout << "14. Buscar servicio por ID" << endl;
        cout << "15. Buscar servicio por nombre" << endl;
        cout << "16. Registrar administrador" << endl;
        cout << "17. Listar administradores" << endl;
        cout << "20. Cerrar sesion" << endl;

        opcion = leerEntero("Seleccione una opcion: ");
        cout << endl;

        switch(opcion) {

            case 1: {
                string nombre, telefono, email, contrasena, cedula, direccion;
                cout << "Nombre del dueno: ";
                getline(cin, nombre);
                cout << "Telefono: ";
                getline(cin, telefono);
                cout << "Email: ";
                getline(cin, email);
                cout << "Contrasena: ";
                getline(cin, contrasena);
                cout << "Cedula: ";
                getline(cin, cedula);
                cout << "Direccion: ";
                getline(cin, direccion);

                Dueno* dueno = new Dueno(nombre, telefono, email, contrasena, cedula, direccion);
                gestorDuenos.agregarDueno(dueno);

                cout << "Dueno registrado con ID: " << dueno->getIdSistema() << endl;
                break;
            }

            case 2: {
                string id;
                cout << "ID dueno: ";
                getline(cin, id);
                gestorDuenos.editarDueno(id);
                break;
            }

            case 3: {
                string id;
                cout << "ID dueno: ";
                getline(cin, id);
                gestorDuenos.eliminarDueno(id);
                break;
            }

            case 4: {
                string id;
                cout << "ID dueno: ";
                getline(cin, id);
                gestorDuenos.buscarDuenoPorID(id);
                break;
            }

            case 5: {
                string nombre;
                cout << "Nombre: ";
                getline(cin, nombre);
                gestorDuenos.buscarDuenoPorNombre(nombre);
                break;
            }

            case 6: {
                string nombre, telefono, email, contrasena, especialidad;
                cout << "Nombre del veterinario: ";
                getline(cin, nombre);
                cout << "Telefono: ";
                getline(cin, telefono);
                cout << "Email: ";
                getline(cin, email);
                cout << "Contrasena: ";
                getline(cin, contrasena);
                cout << "Especialidad: ";
                getline(cin, especialidad);

                Veterinario* v = new Veterinario(nombre, telefono, email, contrasena, especialidad);
                gestorVeterinarios.agregarVeterinario(v);

                cout << "Veterinario registrado con ID: " << v->getIdSistema() << endl;
                break;
            }

            case 7: {
                gestorVeterinarios.listarVeterinarios();
                break;
            }

            case 8: {
                string especialidad;
                cout << "Especialidad: ";
                getline(cin, especialidad);
                gestorVeterinarios.listarPorEspecialidad(especialidad);
                break;
            }

            case 9: {
                string id;
                cout << "ID del veterinario: ";
                getline(cin, id);
                gestorVeterinarios.editarVeterinario(id);
                break;
            }

            case 10: {
                string id;
                cout << "ID del veterinario: ";
                getline(cin, id);
                gestorVeterinarios.eliminarVeterinario(id);
                break;
            }

            case 11: {
                cout << "Usa el menu recepcionista para registrar servicios " << endl;
                break;
            }

            case 12: {
                string id;
                cout << "ID servicio: ";
                getline(cin, id);
                gestorServiciosMedicos.editarServicio(id);
                gestorServiciosEsteticos.editarServicio(id);
                break;
            }

            case 13: {
                string id;
                cout << "ID servicio: ";
                getline(cin, id);
                gestorServiciosMedicos.eliminarServicio(id);
                gestorServiciosEsteticos.eliminarServicio(id);
                break;
            }

            case 14: {
                string id;
                cout << "ID servicio: ";
                getline(cin, id);
                gestorServiciosMedicos.buscarServicioPorID(id);
                gestorServiciosEsteticos.buscarServicioPorID(id);
                break;
            }

            case 15: {
                string nombre;
                cout << "Nombre: ";
                getline(cin, nombre);
                gestorServiciosMedicos.buscarServicioPorNombre(nombre);
                gestorServiciosEsteticos.buscarServicioPorNombre(nombre);
                break;
            }

            case 16: {
                string nombre, telefono, email, contrasena;

            

                cout << " --- REGISTRAR ADMINISTRADOR ---" << endl;

                cout << "Nombre: ";
                getline(cin, nombre);

                cout << "Telefono: ";
                getline(cin, telefono);

                cout << "Email: ";
                getline(cin, email);

                cout << "Contrasena: ";
                getline(cin, contrasena);

                Administrador* admin = new Administrador(nombre, telefono, email, contrasena);
                administradores.push_back(admin);

                cout << "Administrador registrado con ID: "
                     << admin->getIdSistema() << endl;

                break;
            }

            case 17: {
                cout << " --- LISTA DE ADMINISTRADORES ---" << endl;

                if (administradores.empty()) {
                    cout << "No hay administradores registrados" << endl;
                    break;
                }

                for (auto admin : administradores) {
                    admin->mostrarInfo();
                }

                break;
            }

            case 20: {
                cerrarSesion();
                break;
            }

            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }

    } while(opcion != 20);
}                                                                                       // CAMBIADO HASTA AQUI 
 
 

	   	void menuDueno () {
             int opcion;
             do {
             cout << endl;
             cout << "--- MENU DUENO ---" << endl;
             cout << "1. Ver mis mascotas" << endl;
             cout << "2. Buscar mascota por nombre" << endl;
             cout << "3. Ver historial medico de una mascota" << endl;
             cout << "4. Programar cita" << endl;
             cout << "5. Ver mis citas" << endl;
             cout << "6. Cancelar cita" << endl;
             cout << "7. Reprogramar cita" << endl;
             cout << "8. Agregar mascota" << endl;
             cout << "9. Eliminar mascota" << endl;
             cout << "10. Editar mascota" << endl;
             cout << "11. Ver veterinarios" << endl;
             cout << "12. Listar servicios" << endl;
             cout << "13. Buscar servicio por nombre" << endl;
             cout << "14. Cerrar sesion" << endl;
             opcion = leerEntero ("Seleccione una opcion: ");
             cout << endl;

        switch (opcion) {
     	    case 1: {
	            gestorMascotas.listarMascotasDeDueno (usuarioActual -> getIdSistema ());
				break;
				}
            case 2: {
                string nombreMascota;
                cout << "Nombre de la mascota: ";
                getline (cin, nombreMascota);
                Mascota* mascota = gestorMascotas.getMascotaPorNombre (nombreMascota, usuarioActual -> getIdSistema ());
                if (mascota == NULL) {
                    cout << "Mascota no encontrada o no pertenece a este dueno." << endl;
                } else {
                    mascota -> mostrarInfo ();
                }
                break;
                }
            case 3: {
                string idMascota;
                cout << "ID de la mascota: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);

                if (mascota == NULL or mascota -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "Mascota no encontrada o no pertenece a este dueno." << endl;
                } else {
                    mascota -> mostrarHistorial();
                }
                break;
                }
            case 4: {
                string idMascota;
                cout << "ID de la mascota: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);
                if (mascota == NULL) {
                    cout << "Mascota no encontrada." << endl;
                    break;
                }
                if (mascota -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "Solo puede agendar citas para sus mascotas." << endl;
                    break;
                }
                string idVeterinario;
                cout << "ID del veterinario: ";
                getline(cin, idVeterinario);
                Veterinario* veterinario = gestorVeterinarios.getVeterinario(idVeterinario);
                if (veterinario == NULL) {
                    cout << "Veterinario no encontrado." << endl;
                    break;
                }
                cout << "Servicios medicos disponibles:" << endl;
                gestorServiciosMedicos.listarServicios ();
                cout << "Servicios esteticos disponibles: " << endl;
                gestorServiciosEsteticos.listarServicios ();
                string idServicio;
                cout << "ID del servicio: ";
                getline (cin, idServicio);
                Servicio* servicio = gestorServiciosMedicos.getServicio (idServicio);
                if (servicio == NULL) {
                    servicio = gestorServiciosEsteticos.getServicio (idServicio);
                }
                if (servicio == NULL) {
                    cout << "Servicio no encontrado." << endl;
                    break;
                }
                cout << "Ingrese la fecha de la cita:" << endl;
                string fecha = leerFechaValida ();
                cout << "Ingrese la hora de la cita:" << endl;
                string hora = leerHoraValida ();
                gestorCitas.agregarCita (new Cita (fecha, hora, servicio, veterinario, mascota));
                break;
            }
            case 5: {
                Dueno* dueno = (Dueno*) usuarioActual;
                gestorCitas.listarCitasPorDueno (dueno -> getNombre ());
                break;
            }
            case 6: {
                string idCita;
                cout << "ID de la cita: ";
                getline(cin, idCita);
                Cita* cita = gestorCitas.getCita(idCita);
                if (cita == NULL) {
                    cout << "Cita no encontrada." << endl;
                    break;
                }
                if (cita -> getMascotaAtendida () -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "Solo puede cancelar citas de sus mascotas." << endl;
                    break;
                }
                gestorCitas.eliminarCita(idCita);
                break;
            }
            case 7: {
                string idCita;
                cout << "ID de la cita: ";
                getline(cin, idCita);
                Cita* cita = gestorCitas.getCita(idCita);
                if (cita == NULL) {
                    cout << "Cita no encontrada." << endl;
                    break;
                }
                if (cita -> getMascotaAtendida () -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "Solo puede reprogramar citas de sus mascotas." << endl;
                    break;
                }
                cout << "Ingrese la nueva fecha:" << endl;
                string fecha = leerFechaValida ();
                cout << "Ingrese la nueva hora:" << endl;
                string hora = leerHoraValida ();
                gestorCitas.reprogramarCita(idCita, fecha, hora);
                break;
            }
            case 8: {
                Dueno* dueno = (Dueno*) usuarioActual;
                string nombre;
                cout << "Nombre: ";
                getline(cin, nombre);
                int edad = leerEdadValida ("Edad: ");
                Mascota* mascota = new Mascota(nombre, edad, dueno);
                gestorMascotas.agregarMascota(mascota);
                cout << "Mascota registrada con ID: " << mascota->getIdMascota() << endl;
                break;
            }
            case 9: {
                string idMascota;
                cout << "ID: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);
                if (mascota == NULL or mascota -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "No valida." << endl;
                } else {
                    gestorMascotas.eliminarMascota(idMascota);
                }
                break;
            }
            case 10: {
                string idMascota;
                cout << "ID: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);
                if (mascota == NULL or mascota -> getPropietario () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
                    cout << "No valida." << endl;
                } else {
                    string nombre;
                    cout << "Nuevo nombre: ";
                    getline(cin, nombre);
                    int edad = leerEdadValida ("Edad: ");
                    mascota->setNombre(nombre);
                    mascota->setEdad(edad);
                }
                break;
            }
            case 11: {
			   	gestorVeterinarios.listarVeterinarios ();
				break;
					}
            case 12: {
                cout << "Servicios medicos disponibles:" << endl;
                gestorServiciosMedicos.listarServicios();
                cout << endl << "Servicios esteticos disponibles:" << endl;
                gestorServiciosEsteticos.listarServicios();
                break;
            }
            case 13: {
                string nombre;
                cout << "Ingrese el nombre del servicio: ";
                getline(cin, nombre);
                cout << "Resultados en servicios medicos:" << endl;
                gestorServiciosMedicos.buscarServicioPorNombre(nombre);
                cout << "Resultados en servicios esteticos:" << endl;
                gestorServiciosEsteticos.buscarServicioPorNombre(nombre);
                break;
            }
            case 14: {
                cerrarSesion();
                cout << "Sesion cerrada." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
            }
        }

    } while (opcion != 14);
}
	  
	    void menuVeterinario() {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "--- MENU VETERINARIO ---" << endl;
	            cout << "1. Registrar mascota" << endl;
	            cout << "2. Consultar mascota por ID" << endl;
	            cout << "3. Consultar mascota por nombre" << endl;
	            cout << "4. Actualizar mascota" << endl;
	            cout << "5. Eliminar mascota" << endl;
	            cout << "6. Ver historial de mascota" << endl;
	            cout << "7. Modificar el historial de una mascota" << endl;
	            cout << "8. Ver agenda del dia" << endl;
	            cout << "9. Completar cita" << endl;
	            cout << "10. Cerrar sesion" << endl;
	            opcion = leerEntero ("Seleccione una opcion: ");
	            cout << endl;
	
	            switch (opcion) {
	                case 1: {
	                	string idDueno;
				        cout << "ID del dueno: ";
				        getline (cin, idDueno);
				        Dueno* dueno = gestorDuenos.getDueno (idDueno);
				        if (dueno == NULL) {
				            cout << "Dueno no encontrado." << endl;
				            break;
				        }
				
				        string nombre;
				        string especie;
				        string raza;
				        int edad;
				
				        cout << "Nombre de la mascota: ";
				        getline (cin, nombre);
				        cout << "Especie: ";
				        getline (cin, especie);
				        cout << "Raza: ";
				        getline (cin, raza);
				        edad = leerEdadValida ("Edad: ");
				
				        Mascota* mascota = new Mascota (nombre, especie, raza, edad, dueno);
				        gestorMascotas.agregarMascota (mascota);
				        cout << "Mascota registrada con ID: " << mascota -> getIdMascota () << endl;
						break;
					}
	                case 2: {
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    gestorMascotas.buscarMascota (idMascota);
	                    break;
	                }
	                case 3: {
	                    string nombreMascota;
	                    cout << "Nombre de la mascota: ";
	                    getline (cin, nombreMascota);
	                    gestorMascotas.buscarMascotaPorNombre (nombreMascota);
	                    break;
	                }
	                case 4: {
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    gestorMascotas.editarMascota (idMascota);
	                    break;
	                }
	                case 5: {
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    gestorMascotas.eliminarMascota(idMascota);
	                    break;
	                }
	                case 6: {
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    Mascota* mascota = gestorMascotas.getMascota (idMascota);
	                    if (mascota == NULL) {
	                        cout << "Mascota no encontrada." << endl;
	                        break;
	                    } 
	                    mascota -> mostrarHistorial ();
	                    break;
	                }
	                case 7: {
	                    string idMascota;
	                    string entrada;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    Mascota* mascota = gestorMascotas.getMascota (idMascota);
	                    if (mascota == NULL) {
	                        cout << "Mascota no encontrada." << endl;
	                        break;
	                    }
	                    cout << "Nueva entrada: ";
	                    getline (cin, entrada);
	                        mascota -> agregarAlHistorial (entrada);
	                    break;
	                }
	                case 8: {
	                    cout << "Ingrese la fecha para revisar la agenda:" << endl;
	                    string fecha = leerFechaValida ();
	                    gestorCitas.listarAgendaVeterinario (usuarioActual -> getIdSistema (), fecha);
	                    break;
	                }
	                case 9: {
	                	string idCita;
				        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
				            cout << "Cita no encontrada." << endl;
				            break;
				        }
				        if (cita -> getVeterinarioAsignado () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
				            cout << "Solo puede completar sus propias citas." << endl;
				            break;
				        }
			
				        Servicio* servicio = cita -> getServicioSolicitado ();
						string diagnostico = servicio -> procesarServicio ();
						cita -> completarCita (diagnostico);
						cout << "Cita completada y guardada en el historial." << endl;
						break;
					}
	                case 10: {
	                	cerrarSesion ();
						break;
					}
	                default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	            }
	        } while (opcion != 10);
	    }
	
	    void menuRecepcionista() {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "--- MENU RECEPCIONISTA ---" << endl;
	            cout << "1. Registrar dueno" << endl;
	            cout << "2. Editar dueno" << endl;
                cout << "3. Eliminar dueno" << endl;
                cout << "4. Buscar dueno por ID" << endl;
                cout << "5. Buscar dueno por nombre" << endl;
                cout << "6. Registrar veterinario" << endl;
	            cout << "7. Listar veterinarios" << endl;
	            cout << "8. Buscar veterinarios por especialidad" << endl;
	            cout << "9. Actualizar veterinario" << endl;
	            cout << "10. Eliminar veterinario" << endl;
                cout << "11. Registrar servicio" << endl;
                cout << "12. Editar servicio" << endl;
                cout << "13. Eliminar servicio" << endl;
                cout << "14. Buscar servicio por ID" << endl;
                cout << "15. Buscar servicio por nombre" << endl;
                cout << "16. Programar cita" << endl;
	            cout << "17. Consultar citas por fecha" << endl;
	            cout << "18. Cancelar cita" << endl;
	            cout << "19. Reprogramar cita" << endl;
                cout << "20. Cerrar sesion" << endl;
                        
			    opcion = leerEntero ("Seleccione una opcion: ");
	            cout << endl;
	
				switch (opcion) {
	                case 1: {
                        string nombre;
                        string telefono;
                        string email;
                        string contrasena;
                        string cedula;
                        string direccion;
                        cout << "Nombre del dueno: ";
                        getline (cin, nombre);
                        cout << "Telefono: ";
                        getline (cin, telefono);
                        cout << "Email: ";
                        getline (cin, email);
                        cout << "Contrasena: ";
                        getline (cin, contrasena);
                        cout << "Cedula: ";
                        getline (cin, cedula);
                        cout << "Direccion: ";
                        getline (cin, direccion);
                        Dueno* dueno = new Dueno (nombre, telefono, email, contrasena, cedula, direccion);
                        gestorDuenos.agregarDueno (dueno);
                        cout << "Dueno registrado con ID: " << dueno -> getIdSistema () << endl;
						break;
					}
	                case 2: {
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.editarDueno(id); 
						break;
					}
	                case 3: {
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.eliminarDueno(id);
						break;
					}
	                case 4: {
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.buscarDuenoPorID(id);
	                    break;
	                }
	                case 5: {
                        string nombre;
                        cout << "Nombre: ";
                        getline(cin, nombre);
                        gestorDuenos.buscarDuenoPorNombre(nombre);
	                    break;
	                }
	                case 6: {
                        string nombre;
                        string telefono;
                        string email;
                        string contrasena;
                        string especialidad;
                        cout << "Nombre del veterinario: ";
                        getline (cin, nombre);
                        cout << "Telefono: ";
                        getline (cin, telefono);
                        cout << "Email: ";
                        getline (cin, email);
                        cout << "Contrasena: ";
                        getline (cin, contrasena);
                        cout << "Especialidad: ";
                        getline (cin, especialidad);
                        Veterinario* veterinario = new Veterinario (nombre, telefono, email, contrasena, especialidad);
                        gestorVeterinarios.agregarVeterinario (veterinario);
                        cout << "Veterinario registrado con ID: " << veterinario -> getIdSistema () << endl;
						break;
					}  
	                case 7: {
	                	gestorVeterinarios.listarVeterinarios ();
						break;
					}
	                case 8: {
	                    string especialidad;
	                    cout << "Especialidad: ";
	                    getline (cin, especialidad);
	                    gestorVeterinarios.listarPorEspecialidad (especialidad);
	                    break;
	                }
	                case 9: {
	                    string idVeterinario;
	                    cout << "ID del veterinario: ";
	                    getline (cin, idVeterinario);
	                    gestorVeterinarios.editarVeterinario (idVeterinario);
	                    break;
	                }
	                case 10: {
	                    string idVeterinario;
	                    cout << "ID del veterinario: ";
	                    getline(cin, idVeterinario);
	                    gestorVeterinarios.eliminarVeterinario (idVeterinario);
	                    break;
	                }
	                case 11: {
                        int opcionServicio;
                        cout << "1. Servicio medico" << endl;
                        cout << "2. Servicio estetico" << endl;
                        opcionServicio = leerEntero ("Seleccione una opcion: ");
                        string nombre;
                        string descripcion;
                        double precioBase;
                        int duracionMinutos;
                        cout << "Nombre del servicio: ";
                        getline (cin, nombre);
                        cout << "Descripcion: ";
                        getline (cin, descripcion);
                        cout << "Precio base: ";
                        cin >> precioBase;
                        cin.ignore ();
                        duracionMinutos = leerEntero ("Duracion en minutos: ");
                        if (opcionServicio == 1) {
                        	bool requiereDiagnostico;
                        	int opcion_diag;
                        	do {
	                            cout << "1. Requiere diagnostico" << endl;
	                            cout << "2. No requiere diagnostico" << endl;
	                            opcion_diag = leerEntero ("Seleccione una opcion: ");
	                            if (opcion_diag == 1) {
	                            	requiereDiagnostico = true;
								}
								else if (opcion_diag == 2) {
	                            	requiereDiagnostico = false;
								}
								else {
									cout << "Opcion no valida. " << endl;
								}
							}
							while (opcion_diag != 1 and opcion_diag != 2);
                            ServicioMedico* servicio = new ServicioMedico (nombre, descripcion, precioBase, duracionMinutos, requiereDiagnostico);
                            gestorServiciosMedicos.agregarServicio (servicio);
                            cout << "Servicio medico agregado con ID: " << servicio -> getIdServicio () << endl;
                        }
                        else if (opcionServicio == 2) {
                            string tipoEstetica;
                            cout << "Tipo de estetica: ";
                            getline (cin, tipoEstetica);
                            ServicioEstetico* servicio = new ServicioEstetico (nombre, descripcion, precioBase, duracionMinutos, tipoEstetica);
                            gestorServiciosEsteticos.agregarServicio (servicio);
                            cout << "Servicio estetico agregado con ID: " << servicio -> getIdServicio () << endl;
                        }
                        else {
                            cout << "Opcion no valida." << endl;
                        }
                        break;
                    }
                    case 12: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.editarServicio(id);
                        gestorServiciosEsteticos.editarServicio(id);
                        break;
                    }
                    case 13: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.eliminarServicio(id);
                        gestorServiciosEsteticos.eliminarServicio(id);
                        break;
                    }
                    case 14: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.buscarServicioPorID(id);
                        gestorServiciosEsteticos.buscarServicioPorID(id);
                        break;
                    }
                    case 15: {
                        string nombre;
                        cout << "Nombre: ";
                        getline(cin, nombre);
                        gestorServiciosMedicos.buscarServicioPorNombre(nombre);
                        gestorServiciosEsteticos.buscarServicioPorNombre(nombre);
                        break;
                    }
	                case 16: {
	                	string idMascota;
				        cout << "ID de la mascota: ";
				        getline (cin, idMascota);
				        Mascota* mascota = gestorMascotas.getMascota (idMascota);
				        if (mascota == NULL) {
				            cout << "Mascota no encontrada." << endl;
				            break;
				        }
				        string idVeterinario;
				        cout << "ID del veterinario: ";
				        getline (cin, idVeterinario);
				        Veterinario* veterinario = gestorVeterinarios.getVeterinario (idVeterinario);
				        if (veterinario == NULL) {
				            cout << "Veterinario no encontrado." << endl;
				            break;
				        }
				        cout << "Servicios medicos disponibles:" << endl;
				        gestorServiciosMedicos.listarServicios ();
				        cout << "Servicios esteticos disponibles: " << endl;
				        gestorServiciosEsteticos.listarServicios ();
				        string idServicio;
				        cout << "ID del servicio: ";
				        getline (cin, idServicio);
				        Servicio* servicio = gestorServiciosMedicos.getServicio (idServicio);
				        if (servicio == NULL) {
				            servicio = gestorServiciosEsteticos.getServicio (idServicio);
				        }
				        if (servicio == NULL) {
				            cout << "Servicio no encontrado." << endl;
				            break;
				        }
				        cout << "Ingrese la fecha de la cita:" << endl;
				        string fecha = leerFechaValida ();
				        cout << "Ingrese la hora de la cita:" << endl;
				        string hora = leerHoraValida ();
				        gestorCitas.agregarCita (new Cita (fecha, hora, servicio, veterinario, mascota));
	                    break;
					}  
	                case 17: {
	                    cout << "Ingrese la fecha para consultar citas:" << endl;
	                    string fecha = leerFechaValida ();
	                    gestorCitas.listarCitasPorFecha (fecha);
	                    break;
	                }
	                case 18: {
	                	string idCita;
		     	        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
			            cout << "Cita no encontrada." << endl;
			                 break;
			        }
				        gestorCitas.eliminarCita (idCita);
						break;
					}
	                case 19: {
	                	string idCita;
				        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
			            cout << "Cita no encontrada." << endl;
		     	            break;
				        }
				
				        cout << "Ingrese la nueva fecha:" << endl;
				        string fecha = leerFechaValida ();
				        cout << "Ingrese la nueva hora:" << endl;
				        string hora = leerHoraValida ();
				        gestorCitas.reprogramarCita (idCita, fecha, hora);
						break;
					}
                    case 20: {
                        cerrarSesion();
                        break;
                    }                                                                               
	                
				        default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	                    
	            }
	        } 
			while (opcion != 20);
	    }
	    void ejecutar () {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "===== SISTEMA VETERINARIA =====" << endl;
	            cout << "1. Iniciar sesion" << endl;
	            cout << "2. Registrar recepcionista" << endl;
	            cout << "3. Registrar administrador" << endl;                                                         // AGREGADO 
	            cout << "4. Salir" << endl;
	            opcion = leerEntero ("Seleccione una opcion: ");
	            cout << endl;
	
	            switch (opcion) {
	               
				    case 1: {
				    	  
						  string idSistema;      
                          string contrasena;     

	                	
	                    cout << "ID del usuario: ";
	                    getline (cin, idSistema);
	                    cout << "Contrasena: ";
	                    getline (cin, contrasena);
	
	            
					    if (iniciarSesion(idSistema, contrasena)) {                                                 // CAMBIADO DESDE AQUI 
                            cout << "Sesion iniciada como " << usuarioActual->getRol() << "." << endl;

                        if (usuarioActual->getRol() == "Dueno") {
                            menuDueno();
                           } 
                        else if (usuarioActual->getRol() == "Veterinario") {
                            menuVeterinario();
                           } 
                         else if (usuarioActual->getRol() == "Administrador") {
                            menuAdministrador();
                          } 
                        else {
                            menuRecepcionista();
                         }
                       } 
                       else {
                       cout << "Contrasena o ID no validos." << endl;
                        }

                                                                                                                    // CAMBIADO HASTA AQUI
	                	
						break;
					}
	                  
			          
	                case 2: {
                        string nombre;
                        string telefono;
                        string email;
                        string contrasena;
                        string turno;
                        cout << "Nombre del recepcionista: ";
                        getline (cin, nombre);
                        cout << "Telefono: ";
                        getline (cin, telefono);
                        cout << "Email: ";
                        getline (cin, email);
                        cout << "Contrasena: ";
                        getline (cin, contrasena);
                        cout << "Ingrese el turno del recepcionista:" << endl;
                        turno = leerTurnoValido ();
                        Recepcionista* recepcionista = new Recepcionista (nombre, telefono, email, contrasena, turno);
                        recepcionistas.push_back (recepcionista);
                        cout << "Recepcionista registrado con ID: " << recepcionista -> getIdSistema () << endl;
						break;
					}
	               
				    case 3: {                                                                                                    // CAMBIADO DESDE AQUI 
                        menuAdministrador();   
                        break;
            }                                                                                                                   // CAMBIADO HASTA AQUI 
				    case 4: {                                                                                                   // CAMBIADO AQUI A CASE 4 
	                	cout << "Programa finalizado." << endl;
						break;
					}   
	                default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	            }
	        }
			while (opcion != 4);                                                                                                 // CAMBIADO A 4 
	    }
	
	    ~SistemaVeterinaria () {
	        for (auto recepcionista : recepcionistas) {
	            delete recepcionista;
	        }
	    }
};

int main () {
    SistemaVeterinaria sistema;
    sistema.ejecutar ();
    return 0;
}
