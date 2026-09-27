#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PilaEspera.h"
#include "Eventos.h"
#include "Historial.h"
#include "Puntajes.h"

class Juego
{
private:
	Tablero tablero;
	ColaPiezas cola;
	PilaEspera pila;
	Pieza pieza;
	ColaEventos colaEventos;
	Historial historial;
	
	sf::RenderWindow ventana;
	sf::Font fuente;
	sf::Clock relojCaida;
	sf::Clock relojReplay;
	
	float tiempoCaida;
	float tiempoReplay;
	
	bool juegoIniciado;
	bool pantallaConfiguracion;
	bool juegoPausado;
	bool juegoTerminado;
	bool puntajeRegistrado;
	bool replayAutomatico;
	bool modoReplay;
	bool mostrarTop10Grafico;
	bool especialPendiente;
	
	std::string nombreJugador;
	
	int algoritmoOrdenamiento;
	int puntaje;
	int puntajeFinal;
	int lineasTotales;
	
	RegistroPuntaje top10[10];
	int cantidadTop10;
	
	void inicializarEstructuras();
	void cargarFuente();
	void programarEventosIniciales();
	
	void liberarPila();
	void liberarColaPiezas();
	void reiniciarEstructurasPartida();
	void nuevoJuego();
	
	void procesarEntrada();
	void procesarTexto(const sf::Event &evento);
	void procesarTecla(sf::Keyboard::Key tecla);
	
	void manejarInicio(sf::Keyboard::Key tecla);
	void manejarConfiguracion(sf::Keyboard::Key tecla);
	void manejarGameOver(sf::Keyboard::Key tecla);
	void manejarPausa(sf::Keyboard::Key tecla);
	void manejarPartida(sf::Keyboard::Key tecla);
	
	void iniciarReplay();
	void retrocederReplay();
	void avanzarReplay();
	
	void registrarEstadoActual(char accion);
	void moverHorizontal(int desplazamiento, char accion);
	void rotarActual();
	void bajarManual();
	void usarHold();
	void caidaRapida();
	void deshacerMovimiento();
	void rehacerMovimiento();
	
	void procesarEventosProgramados();
	bool fijarYCrearNuevaPieza();
	void fijarPiezaYContinuar();
	void terminarJuego();
	
	void actualizar();
	void actualizarCaidaAutomatica();
	void registrarPuntajeSiCorresponde();
	void actualizarReplay();
	
	void dibujar();
	void dibujarJuego();
	
public:
	Juego();
	~Juego();
	
	void ejecutar();
};

#endif
