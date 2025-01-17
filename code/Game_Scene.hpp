/*
 * GAME SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#ifndef GAME_SCENE_HEADER
#define GAME_SCENE_HEADER

#include <map>
#include <list>
#include <memory>

#include <basics/Canvas>
#include <basics/Id>
#include <basics/Scene>
#include <basics/Texture_2D>
#include <basics/Timer>

#include "Sprite.hpp"

namespace example
{

    using basics::Id;
    using basics::Timer;
    using basics::Canvas;
    using basics::Texture_2D;

    class Game_Scene : public basics::Scene
    {

        // Estos typedefs pueden ayudar a hacer el código más compacto y claro:

        typedef std::shared_ptr < Sprite     >     Sprite_Handle;
        typedef std::list< Sprite_Handle     >     Sprite_List;
        typedef std::shared_ptr< Texture_2D  >     Texture_Handle;
        typedef std::map< Id, Texture_Handle >     Texture_Map;
        typedef basics::Graphics_Context::Accessor Context;

        /**
         * Representa el estado de la escena en su conjunto.
         */
        enum State
        {
            LOADING,
            RUNNING,
            ERROR
        };

        /**
         * Representa el estado del juego cuando el estado de la escena es RUNNING.
         */
        enum Gameplay_State
        {
            UNINITIALIZED,
            WAITING_TO_START,
            PLAYING,
            BALL_LEAVING,
        };

    private:

        /**
         * Array de estructuras con la información de las texturas (Id y ruta) que hay que cargar.
         */
        static struct   Texture_Data { Id id; const char * path; } textures_data[];

        /**
         * Número de items que hay en el array textures_data.
         */
        static unsigned textures_count;

    private:
//VELOCIDADES DE COCHES Y HISTORIAS
        static constexpr float   car1_speed = 200.f;
        static constexpr float   car2_speed = 300.f;
        static constexpr float   car3_speed = 360.f;
        static constexpr float   truck_speed = 400.f;
        static constexpr float   ball_speed = 400.f;        ///< Velocidad a la que se mueve la bola (en unideades virtuales por segundo).
        static constexpr float player_speed = 300.f;        ///< Velocidad a la que se mueven ambos jugadores (en unideades virtuales por segundo).

    private:

        State          state;                               ///< Estado de la escena.
        Gameplay_State gameplay;                            ///< Estado del juego cuando la escena está RUNNING.
        bool           suspended;                           ///< true cuando la escena está en segundo plano y viceversa.

        unsigned       canvas_width;                        ///< Ancho de la resolución virtual usada para dibujar.
        unsigned       canvas_height;                       ///< Alto  de la resolución virtual usada para dibujar.

        Texture_Map    textures;                            ///< Mapa  en el que se guardan shared_ptr a las texturas cargadas.
        Sprite_List    sprites;                             ///< Lista en la que se guardan shared_ptr a los sprites creados.

        Sprite       * top_border;                          ///< Puntero al sprite de la lista de sprites que representa el borde superior.
        Sprite       * bottom_border;                       ///< Puntero al sprite de la lista de sprites que representa el borde inferior.
        Sprite       * left_player;                         ///< Puntero al sprite de la lista de sprites que representa al jugador izquierdo.
        Sprite       * right_player;                        ///< Puntero al sprite de la lista de sprites que representa al jugador derecho.
        Sprite       * ball;                                ///< Puntero al sprite de la lista de sprites que representa a la bola.


        Sprite       * left_border;                         ///< Puntero al sprite de la lista de sprites que representa al jugador izquierdo.
        Sprite       * right_border;
        Sprite      *caryellow1;
        Sprite      *caryellow2;
        Sprite      *caryellow3;
        Sprite      *carblue1;
        Sprite      *carblue2;

        Sprite      *truckmidlane1;
        Sprite      *truckmidlane2;

        Sprite      *trucklastlane1;
        Sprite      *trucklastlane2;

        Sprite      *carwhite1;
        Sprite      *carwhite2;
        Sprite      *carwhite3;
        Sprite      *frogcharacter;


        Sprite      *truck;
        Sprite      *road;
        Sprite      *grass;
        Sprite      *water;

        Sprite      *bigturtle1;
        Sprite      *bigturtle2;


        Sprite      *smallturtle1;
        Sprite      *smallturtle2;
        Sprite      *smallturtle3;

        Sprite      *biglog1ml;
        Sprite      *biglog2ml;
        Sprite      *biglog1ll;
        Sprite      *biglog2ll;
        Sprite      *smalllog1;
        Sprite      *smalllog2;
        Sprite      *smalllog3;


        bool           follow_target;                       ///< true si el usuario está tocando la pantalla y su player ir hacia donde toca.
        float          user_target_y;                       ///< Coordenada Y hacia donde debe ir el player del usuario cuando este toca la pantalla.
        float          user_target_x;                       ///< Coordenada X hacia donde debe ir el player del usuario cuando este toca la pantalla.


        Timer          timer;                               ///< Cronómetro usado para medir intervalos de tiempo

    public:

        /**
         * Solo inicializa los atributos que deben estar inicializados la primera vez, cuando se
         * crea la escena desde cero.
         */
        Game_Scene();

        /**
         * Este método lo llama Director para conocer la resolución virtual con la que está
         * trabajando la escena.
         * @return Tamaño en coordenadas virtuales que está usando la escena.
         */
        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        /**
         * Aquí se inicializan los atributos que deben restablecerse cada vez que se inicia la escena.
         * @return
         */
        bool initialize () override;

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a segundo plano.
         */
        void suspend () override;

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a primer plano.
         */
        void resume () override;

        /**
         * Este método se invoca automáticamente una vez por fotograma cuando se acumulan
         * eventos dirigidos a la escena.
         */
        void handle (basics::Event & event) override;

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * actualize su estado.
         */
        void update (float time) override;

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * dibuje su contenido.
         */
        void render (Context & context) override;

    private:

        /**
         * En este método se cargan las texturas (una cada fotograma para facilitar que la
         * propia carga se pueda pausar cuando la aplicación pasa a segundo plano).
         */
        void load_textures ();

        /**
         * En este método se crean los sprites cuando termina la carga de texturas.
         */
        void create_sprites ();

        /**
         * Se llama cada vez que se debe reiniciar el juego. En concreto la primera vez y cada
         * vez que un jugador pierde.
         */
        void restart_game ();

        /**
         * Cuando se ha reiniciado el juego y el usuario toca la pantalla por primera vez se
         * pone la bola en movimiento en una dirección al azar.
         */
        void start_playing ();

        /**
         * Actualiza el estado del juego cuando el estado de la escena es RUNNING.
         */
        void run_simulation (float time);

        /**
         * Controla el player izquierdo usando una inteligencia artificial muy básica.
         */
        void update_ai ();

        /**
         * Hace que el player derecho se mueva hacia el punto de la pantalla que toca el usuario.
         */
        void update_user ();

        /**
         * Comprueba las colisiones de la bola con el escenario y con los players.
         */
        void check_ball_collisions ();

        /**
         * Dibuja la textura con el mensaje de carga mientras el estado de la escena es LOADING.
         * La textura con el mensaje se carga la primera para mostrar el mensaje cuanto antes.
         * @param canvas Referencia al Canvas con el que dibujar la textura.
         */
        void render_loading (Canvas & canvas);

        /**
         * Dibuja la escena de juego cuando el estado de la escena es RUNNING.
         * @param canvas Referencia al Canvas con el que dibujar.
         */
        void render_playfield (Canvas & canvas);

    };

}

#endif
