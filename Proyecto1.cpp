#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

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
	        entradas.push_back(entrada);
	    }
	
	    void mostrarHistorial () const {
	        if (entradas.empty()) {
	            cout << "No hay registros en el historial medico.\n";
	            return;
	        }
	        cout << endl << "Historial medico:" << endl;
	        cout << "Altura: " << altura << endl;
	        cout << "Peso: " << peso << endl;
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
	    static string generarIdMascota() {
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
	    void mostrarInfo () const override {
	        cout << "Servicio medico - ID: " << idServicio << ", Nombre: " << nombre << ", Precio final (12%): $" << fixed << setprecision(2) << calcularPrecio(15) << endl;
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
	        if (productos.size () >= 3) {
	        	return 3;
			}
			else if (productos.size () >= 5) {
				return 5;
			}
			else if (productos.size () >= 8) {
				return 7;
			}
			else {
				return 0;
			}
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
	            cout << "No hay servicios registrados.\n";
	            return;
	        }
	        for (const auto& servicio : servicios) {
	            servicio -> mostrarInfo ();
	        }
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
	            cout << "No hay duenos registrados.\n";
	            return;
	        }
	        for (const auto& dueno : duenos) {
	            dueno -> mostrarInfo();
	        }
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
		//Getters
		Mascota* getMascota (const string& idMascota) const {
        for (auto mascota : mascotas) {
            if (mascota -> getIdMascota () == idMascota) {
                return mascota;
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
	    Usuario* usuarioActual;
	    
		//Metodos
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
	    void registrarDueno () {
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
	    }
	    void registrarVeterinario () {
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
	    }
	    void registrarRecepcionista () {
	        string nombre;
	        string telefono;
	        string email;
	        string contrasena;
	        string turno;
	
	        cout << "Nombre del recepcionista: ";
	        getline(cin, nombre);
	        cout << "Telefono: ";
	        getline(cin, telefono);
	        cout << "Email: ";
	        getline(cin, email);
	        cout << "Contrasena: ";
	        getline(cin, contrasena);
	        cout << "Turno (hh:mm - hh:mm): ";
	        getline(cin, turno);
	
	        Recepcionista* recepcionista = new Recepcionista (nombre, telefono, email, contrasena, turno);
	        recepcionistas.push_back( recepcionista);
	        cout << "Recepcionista registrado con ID: " << recepcionista -> getIdSistema () << endl;
	    }
	public:
	    //Constructor
		SistemaVeterinaria () : usuarioActual (NULL) {}
		
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
	   	void menuDueno () {                                                          // CAMBIADO DESDE AQUI 
             int opcion;
             do {
             cout << endl;
             cout << "--- MENU DUENO ---" << endl;
             cout << "1. Ver mis mascotas" << endl;
             cout << "2. Ver historial medico de una mascota" << endl;
             cout << "3. Programar cita" << endl;
             cout << "4. Ver mis citas" << endl;
             cout << "5. Cancelar cita" << endl;
             cout << "6. Reprogramar cita" << endl;
             cout << "7. Agregar mascota" << endl;
             cout << "8. Eliminar mascota" << endl;
             cout << "9. Editar mascota" << endl;
             cout << "10. Ver veterinarios" << endl;
             cout << "11. Listar servicios" << endl;
             cout << "12. Buscar servicio por nombre" << endl;
             cout << "13. Cerrar sesion" << endl;
             cout << "Seleccione una opcion: ";
             cin >> opcion;
             cin.ignore();
             cout << endl;

        switch (opcion) {
        	        	
     	    case 1: {
	            gestorMascotas.listarMascotasDeDueno (usuarioActual -> getIdSistema ());
				break;
				}


            case 2: {
                string idMascota;
                cout << "ID de la mascota: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);

                if (mascota == NULL || mascota->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
                    cout << "Mascota no encontrada o no pertenece a este dueno." << endl;
                } else {
                    mascota->mostrarHistorial();
                }
                break;
                }

            case 3: {
                string idMascota;
                cout << "ID de la mascota: ";
                getline(cin, idMascota);
                Mascota* mascota = gestorMascotas.getMascota(idMascota);

                if (mascota == NULL) {
                    cout << "Mascota no encontrada." << endl;
                    break;
                }

                if (usuarioActual->getRol() == "Dueno" &&
                    mascota->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
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
                gestorServiciosMedicos.listarServicios();

                cout << "Servicios esteticos disponibles:" << endl;
                gestorServiciosEsteticos.listarServicios();

                string idServicio;
                cout << "ID del servicio: ";
                getline(cin, idServicio);

                Servicio* servicio = gestorServiciosMedicos.getServicio(idServicio);
                if (servicio == NULL) {
                    servicio = gestorServiciosEsteticos.getServicio(idServicio);
                }

                if (servicio == NULL) {
                    cout << "Servicio no encontrado." << endl;
                    break;
                }

                string fecha, hora;
                cout << "Fecha (dd/mm/aaaa): ";
                getline(cin, fecha);
                cout << "Hora (hh:mm): ";
                getline(cin, hora);

                gestorCitas.agregarCita(new Cita(fecha, hora, servicio, veterinario, mascota));
                break;
            }

            case 4: {
                if (usuarioActual->getRol() == "Dueno") {
                    Dueno* dueno = (Dueno*) usuarioActual;
                    gestorCitas.listarCitasPorDueno(dueno->getNombre());
                }
                break;
            }

            case 5: {
                string idCita;
                cout << "ID de la cita: ";
                getline(cin, idCita);

                Cita* cita = gestorCitas.getCita(idCita);
                if (cita == NULL) {
                    cout << "Cita no encontrada." << endl;
                    break;
                }

                if (usuarioActual->getRol() == "Dueno" &&
                    cita->getMascotaAtendida()->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
                    cout << "Solo puede cancelar citas de sus mascotas." << endl;
                    break;
                }

                gestorCitas.eliminarCita(idCita);
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

                if (usuarioActual->getRol() == "Dueno" &&
                    cita->getMascotaAtendida()->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
                    cout << "Solo puede reprogramar citas de sus mascotas." << endl;
                    break;
                }

                string fecha, hora;
                cout << "Nueva fecha: ";
                getline(cin, fecha);
                cout << "Nueva hora: ";
                getline(cin, hora);

                gestorCitas.reprogramarCita(idCita, fecha, hora);
                break;
            }

            case 7: {
                if (usuarioActual->getRol() != "Dueno") {
                    cout << "Dueno no valido." << endl;
                    break;
                }

                Dueno* dueno = (Dueno*) usuarioActual;
                string nombre;
                int edad;

                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Edad: ";
                cin >> edad;
                cin.ignore();

                Mascota* mascota = new Mascota(nombre, edad, dueno);
                gestorMascotas.agregarMascota(mascota);

                cout << "Mascota registrada con ID: " << mascota->getIdMascota() << endl;
                break;
            }

            case 8: {
                string idMascota;
                cout << "ID: ";
                getline(cin, idMascota);

                Mascota* mascota = gestorMascotas.getMascota(idMascota);

                if (mascota == NULL || mascota->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
                    cout << "No valida." << endl;
                } else {
                    gestorMascotas.eliminarMascota(idMascota);
                }
                break;
            }

            case 9: {
                string idMascota;
                cout << "ID: ";
                getline(cin, idMascota);

                Mascota* mascota = gestorMascotas.getMascota(idMascota);

                if (mascota == NULL || mascota->getPropietario()->getIdSistema() != usuarioActual->getIdSistema()) {
                    cout << "No valida." << endl;
                } else {
                    string nombre;
                    int edad;

                    cout << "Nuevo nombre: ";
                    getline(cin, nombre);
                    cout << "Edad: ";
                    cin >> edad;
                    cin.ignore();

                    mascota->setNombre(nombre);
                    mascota->setEdad(edad);
                }
                break;
            }

            case 10: {
			   	gestorVeterinarios.listarVeterinarios ();
				break;
					}

            case 11: {
                cout << "Servicios medicos disponibles:" << endl;
                gestorServiciosMedicos.listarServicios();

                cout << endl << "Servicios esteticos disponibles:" << endl;
                gestorServiciosEsteticos.listarServicios();
                break;
            }

            case 12: {
                string nombre;
                cout << "Ingrese el nombre del servicio: ";
                getline(cin, nombre);

                cout << "Resultados en servicios medicos:" << endl;
                gestorServiciosMedicos.buscarServicioPorNombre(nombre);

                cout << "Resultados en servicios esteticos:" << endl;
                gestorServiciosEsteticos.buscarServicioPorNombre(nombre);
                break;
            }

            case 13: {
                cerrarSesion();
                cout << "Sesion cerrada." << endl;
                break;
            }

            default: {
                cout << "Opcion no valida." << endl;
            }
        }

    } while (opcion != 13);
}                                                                                        // HASTA AQUI 
	  
	    void menuVeterinario() {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "--- MENU VETERINARIO ---" << endl;
	            cout << "1. Registrar mascota" << endl;
	            cout << "2. Consultar mascota por ID" << endl;
	            cout << "3. Actualizar mascota" << endl;
	            cout << "4. Eliminar mascota" << endl;
	            cout << "5. Ver historial de mascota" << endl;
	            cout << "6. Modificar el historial de una mascota" << endl;
	            cout << "7. Ver agenda del dia" << endl;
	            cout << "8. Completar cita" << endl;
	            cout << "9. Cerrar sesion" << endl;
	            cout << "Seleccione una opcion: ";
	            cin >> opcion;
	            cin.ignore();
	            cout << endl;
	
	            switch (opcion) {
	                case 1: {
	                	string idDueno;
				        cout << "ID del dueno: ";
				        getline (cin, idDueno);
				        Dueno* dueno = gestorDuenos.getDueno (idDueno);
				        if (dueno == NULL) {
				            cout << "Dueno no encontrado." << endl;
				            return;
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
				        cout << "Edad: ";
				        cin >> edad;
				        cin.ignore();
				
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
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    gestorMascotas.editarMascota (idMascota);
	                    break;
	                }
	                case 4: {
	                    string idMascota;
	                    cout << "ID de la mascota: ";
	                    getline (cin, idMascota);
	                    gestorMascotas.eliminarMascota(idMascota);
	                    break;
	                }
	                case 5: {
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
	                case 6: {
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
	                case 7: {
	                    string fecha;
	                    cout << "Fecha (dd/mm/aaaa): ";
	                    getline (cin, fecha);
	                    gestorCitas.listarAgendaVeterinario (usuarioActual -> getIdSistema (), fecha);
	                    break;
	                }
	                case 8: {
	                	string idCita;
				        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
				            cout << "Cita no encontrada." << endl;
				            return;
				        }
				        if (cita -> getVeterinarioAsignado () -> getIdSistema () != usuarioActual -> getIdSistema ()) {
				            cout << "Solo puede completar sus propias citas.";
				            return;
				        }
				
				        string diagnostico;
				        cout << "Diagnostico u observaciones: ";
				        getline (cin, diagnostico);
				        cita -> completarCita (diagnostico);
				        cout << "Cita completada y guardada en el historial." << endl;
						break;
					}
	                case 9: {
	                	cerrarSesion ();
						break;
					}
	                default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	            }
	        } while (opcion != 8);
	    }
	
	    void menuRecepcionista() {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "--- MENU RECEPCIONISTA ---" << endl;
	            cout << "1. Registrar dueno" << endl;
	            cout << "2. Registrar veterinario" << endl;
	            cout << "3. Listar veterinarios" << endl;
	            cout << "4. Buscar veterinarios por especialidad" << endl;
	            cout << "5. Actualizar veterinario" << endl;
	            cout << "6. Programar cita" << endl;
	            cout << "7. Consultar citas por fecha" << endl;
	            cout << "8. Cancelar cita" << endl;
	            cout << "9. Reprogramar cita" << endl;
	            cout << "10. Eliminar veterinario" << endl;
	            cout << "11. Editar dueno" << endl;                                 //DESDE AQUI CAMBIADO 
                cout << "12. Eliminar dueno" << endl;
                cout << "13. Buscar dueno por ID" << endl;
                cout << "14. Buscar dueno por nombre" << endl;
                cout << "15. Editar servicio" << endl;
                cout << "16. Eliminar servicio" << endl;
                cout << "17. Buscar servicio por ID" << endl;
                cout << "18. Buscar servicio por nombre" << endl;
                cout << "19. Cerrar sesion" << endl;                                //HASTA AQUI CAMBIADO 
                        
			    cout << "Seleccione una opcion: ";
	            cin >> opcion;
	            cin.ignore();
	            cout << endl;
	
				switch (opcion) {
	                case 1: {
	                	registrarDueno ();
						break;
					}
	                case 2: {
	                	registrarVeterinario ();
						break;
					}
	                case 3: {
	                	gestorVeterinarios.listarVeterinarios ();
						break;
					}
	                case 4: {
	                    string especialidad;
	                    cout << "Especialidad: ";
	                    getline (cin, especialidad);
	                    gestorVeterinarios.listarPorEspecialidad (especialidad);
	                    break;
	                }
	                case 5: {
	                    string idVeterinario;
	                    cout << "ID del veterinario: ";
	                    getline (cin, idVeterinario);
	                    gestorVeterinarios.editarVeterinario (idVeterinario);
	                    break;
	                }
	                case 6: {
	                	string idMascota;
				        cout << "ID de la mascota: ";
				        getline (cin, idMascota);
				        Mascota* mascota = gestorMascotas.getMascota (idMascota);
				        if (mascota == NULL) {
				            cout << "Mascota no encontrada." << endl;
				            return;
				        }
				        string idVeterinario;
				        cout << "ID del veterinario: ";
				        getline (cin, idVeterinario);
				        Veterinario* veterinario = gestorVeterinarios.getVeterinario (idVeterinario);
				        if (veterinario == NULL) {
				            cout << "Veterinario no encontrado." << endl;
				            return;
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
						    return;
						}
				
				        string fecha;
				        string hora;
				        cout << "Fecha (dd/mm/aaaa): ";
				        getline (cin, fecha);
				        cout << "Hora (hh:mm): ";
				        getline (cin, hora);
				        gestorCitas.agregarCita (new Cita (fecha, hora, servicio, veterinario, mascota));
	                    break;
					}  
	                case 7: {
	                    string fecha;
	                    cout << "Fecha (dd/mm/aaaa): ";
	                    getline (cin, fecha);
	                    gestorCitas.listarCitasPorFecha (fecha);
	                    break;
	                }
	                case 8: {
	                	string idCita;
		     	        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
			            cout << "Cita no encontrada." << endl;
			                 return;
			        }
				        gestorCitas.eliminarCita (idCita);
						break;
					}
	                case 9: {
	                	string idCita;
				        cout << "ID de la cita: ";
				        getline (cin, idCita);
				        Cita* cita = gestorCitas.getCita (idCita);
				        if (cita == NULL) {
			            cout << "Cita no encontrada." << endl;
		     	            return;
				        }
				
				        string fecha;
				        string hora;
				        cout << "Nueva fecha (dd/mm/aaaa): ";
				        getline (cin, fecha);
				        cout << "Nueva hora (hh:mm): ";
				        getline (cin, hora);
				        gestorCitas.reprogramarCita (idCita, fecha, hora);
						break;
					}
	                case 10: {
	                    string idVeterinario;
	                    cout << "ID del veterinario: ";
	                    getline(cin, idVeterinario);
	                    gestorVeterinarios.eliminarVeterinario (idVeterinario);
	                    break;
	                }
	                case 11: {                                                     // CAMBIADO DESDE AQUI 
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.editarDueno(id); 
                        break;
                    }

                    case 12: {
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.eliminarDueno(id);
                        break;
                    }

                    case 13: {
                        string id;
                        cout << "ID dueno: ";
                        getline(cin, id);
                        gestorDuenos.buscarDuenoPorID(id);
                        break;
                    }

                    case 14: {
                        string nombre;
                        cout << "Nombre: ";
                        getline(cin, nombre);
                        gestorDuenos.buscarDuenoPorNombre(nombre);
                        break;
                    }

                          // Servicios
                    case 15: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.editarServicio(id);
                        gestorServiciosEsteticos.editarServicio(id);
                        break;
                    }

                    case 16: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.eliminarServicio(id);
                        gestorServiciosEsteticos.eliminarServicio(id);
                        break;
                    }

                    case 17: {
                        string id;
                        cout << "ID servicio: ";
                        getline(cin, id);
                        gestorServiciosMedicos.buscarServicioPorID(id);
                        gestorServiciosEsteticos.buscarServicioPorID(id);
                        break;
                    }

                    case 18: {
                        string nombre;
                        cout << "Nombre: ";
                        getline(cin, nombre);
                        gestorServiciosMedicos.buscarServicioPorNombre(nombre);
                        gestorServiciosEsteticos.buscarServicioPorNombre(nombre);
                        break;
                    }

                    case 19: {
                        cerrarSesion();
                        break;
                    }                                                                               
	                
				        default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	                    
	            }
	        } 
			while (opcion != 19);                                                                // CAMBIADO HASTA AQUI 
	    }
	    void ejecutar () {
	        int opcion;
	        do {
	            cout << endl;
	            cout << "===== SISTEMA VETERINARIA =====" << endl;
	            cout << "1. Iniciar sesion" << endl;
	            cout << "2. Registrar recepcionista" << endl;
	            cout << "3. Salir" << endl;
	            cout << "Seleccione una opcion: ";
	            cin >> opcion;
	            cin.ignore();
	            cout << endl;
	
	            switch (opcion) {
	                case 1: {
	                    string idSistema;
	                    string contrasena;
	                    cout << "ID del usuario: ";
	                    getline (cin, idSistema);
	                    cout << "Contrasena: ";
	                    getline (cin, contrasena);
	
	                    if (iniciarSesion (idSistema, contrasena)) {
	                        cout << "Sesion iniciada como " << usuarioActual -> getRol() << "." << endl;
	                        if (usuarioActual -> getRol () == "Dueno") {
	                            menuDueno ();
	                        } 
							else if (usuarioActual -> getRol () == "Veterinario") {
	                            menuVeterinario ();
	                        } 
							else {
	                            menuRecepcionista ();
	                        }
	                    } 
						else {
	                        cout << "Contrasena o ID no validos." << endl;
	                    }
	                    break;
	                }
	                case 2: {
	                	registrarRecepcionista ();
						break;
					}
	                case 3: {
	                	cout << "Programa finalizado." << endl;
						break;
					}   
	                default: {
	                	cout << "Opcion no valida." << endl;
						break;
					}
	            }
	        }
			while (opcion != 3);
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
