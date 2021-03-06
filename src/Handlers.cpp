#include "Handlers.h"
#include "Element.h"

namespace handler {

bool IsDipoleArea(const sf::Vector2i & position) {
  Vector2 center = Vector2(DEFAULT_AREA_CENTER_X, DEFAULT_AREA_CENTER_Y);
  return (DEFAULT_AREA_RADIUS > (center - position).Len( ));
}

bool IsFrontArea(const sf::Vector2i & position) {
  float x = position.x;
  float y = position.y;

  return !((x < DEFAULT_AREA_RADIUS) || (x > SCREEN_WIDTH) || (y < 0) || (y > SCREEN_HEIGHT));
}

bool HandleEvent(sf::RenderWindow &window, Store &store)
{
  #ifdef HANDLE_EVENT_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  sf::Event event;
  // DIRECTION_0 is equal  DEFAULT_DIPOLE_DIRECTION.
  static PosssibleDipoleDirections dipole_direction = DIRECTION_0;

  // PHASE_0 is equal DEFAULT_PHASE.
  static PosssibleDipolePhase dipole_phase = PHASE_0;

  while (window.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::Closed:
        window.close( );
        break;
      case sf::Event::MouseButtonPressed:
        HandleMouse(window, event, store, &dipole_direction, &dipole_phase);
        break;
      case sf::Event::KeyPressed:
        HandleKey(window, event, store, &dipole_direction, &dipole_phase);
        break;
    }
  }

  #ifdef HANDLE_EVENT_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif

  return true;
}

int GetTextureIndex(const PosssibleDipolePhase phase) 
{
  switch (phase)
  {
    case PHASE_0:
      return 0;
    case PHASE_36:
      return 1;
    case PHASE_72:
      return 2;
    case PHASE_108:
      return 3;
    case PHASE_144:
      return 4;
    case PHASE_180:
      return 5;
    case PHASE_216:
      return 6;
    case PHASE_252:
      return 7;
    case PHASE_288:
      return 8;
    case PHASE_324:
      return 9;
    default:
      std::cout << "Strange value of phase in file:" << __FILE__ << std::endl;
      std::cout << "In line: " << __LINE__ << std::endl;
      std::cout << "In function: " << __PRETTY_FUNCTION__ << std::endl;
      exit(EXIT_FAILURE);
  }
}


bool HandleMouse(const sf::RenderWindow &window, const sf::Event &event, Store &store,
                 PosssibleDipoleDirections *dipole_direction, PosssibleDipolePhase *dipole_phase) {

  assert(dipole_direction != nullptr);
  assert(dipole_phase != nullptr);

  sf::Vector2i position = sf::Mouse::getPosition(window);
  Wave singular_wave;
  FrontElement front_element;

  switch(event.key.code) {

    case sf::Mouse::Left:
      #ifdef MOUSE_DEBUG
      std::cout << "HandleMouse(): Left" << std::endl;
      #endif /* MOUSE_DEBUG */

      if (IsDipoleArea(position)) {
        Dipole dipole = Dipole(my_math::Vector2(position), GetTextureIndex(*dipole_phase));
        dipole.SetDirection((float)*dipole_direction);
        dipole.SetPhase((float)*dipole_phase);
        store.Push(dipole);

        #ifdef DIPOLE_PHASE_DEBUG
        std::cout << "dipole_phase = " << dipole.GetPhase( ) << std::endl;
        #endif /* DIPOLE_PHASE_DEBAG */

        *dipole_direction = DIRECTION_0;
        *dipole_phase = PHASE_0;
      }

      break;

    case sf::Mouse::Right:
      #ifdef MOUSE_DEBUG
      std::cout << "HandleMouse(): Right" << std::endl;
      std::cout << std::endl;
      #endif /* MOUSE_DEBUG */

      if (IsFrontArea(position)) {
        singular_wave.Push(FrontElement(position));
        store.Push(singular_wave);
      }

      break;
  }

  return true;
}

bool HandleKey(const sf::RenderWindow &window, const sf::Event &event, Store & store, PosssibleDipoleDirections *dipole_direction,
               PosssibleDipolePhase *dipole_phase) {

  assert(dipole_direction != nullptr);
  assert(dipole_phase != nullptr);

  sf::Vector2i position = sf::Mouse::getPosition(window);

  Dipole dipole(Vector2(0,0));

  switch(event.key.code) {

    case sf::Keyboard::Escape:
      store.Clear();
      break;

    // Set phases.
    case sf::Keyboard::Num1:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num1" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_36;
      break;

    case sf::Keyboard::Num2:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num2" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_72;
      break;

    case sf::Keyboard::Num3:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num3" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_108;
      break;

    case sf::Keyboard::Num4:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num4" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_144;
      break;

    case sf::Keyboard::Num5:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num5" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_180;
      break;

    case sf::Keyboard::Num6:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num6" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_216;
      break;

    case sf::Keyboard::Num7:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num7" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_252;
      break;

    case sf::Keyboard::Num8:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num8" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_288;
      break;

    case sf::Keyboard::Num9:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Num9" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_phase = PHASE_324;
      break;

    // Set directions.
    case sf::Keyboard::Q:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Q" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_45;
      break;

    case sf::Keyboard::W:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): W" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_90;
      break;

    case sf::Keyboard::E:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): E" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_135;
      break;

    case sf::Keyboard::R:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): R" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_180;
      break;

    case sf::Keyboard::T:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): T" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_225;
      break;

    case sf::Keyboard::Y:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): Y" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_270;
      break;

    case sf::Keyboard::U:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): U" << std::endl;
      #endif /* KEY_DEBUG */
      *dipole_direction = DIRECTION_315;
      break;

    case sf::Keyboard::X:
        dipole.SetPosition(Vector2(5, 275));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 285));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 295));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 305));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 315));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 325));
        dipole.SetPhase(0);
        store.Push(dipole);
      break;

    case sf::Keyboard::Z:
        dipole.SetPosition(Vector2(5, 275));
        dipole.SetPhase(0);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 285));
        dipole.SetPhase(30);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 295));
        dipole.SetPhase(60);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 305));
        dipole.SetPhase(90);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 315));
        dipole.SetPhase(120);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 325));
        dipole.SetPhase(150);
        store.Push(dipole);

        break;

    case sf::Keyboard::C:
        dipole.SetPosition(Vector2(5, 275));
        dipole.SetPhase(150);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 285));
        dipole.SetPhase(120);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 295));
        dipole.SetPhase(90);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 305));
        dipole.SetPhase(60);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 315));
        dipole.SetPhase(30);
        store.Push(dipole);

        dipole.SetPosition(Vector2(5, 325));
        dipole.SetPhase(0);
        store.Push(dipole);

        break;

    case sf::Keyboard::V:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): V" << std::endl;
      #endif /* KEY_DEBUG */
      {
        DiffractionGrating diffraction_grating = DiffractionGrating(my_math::Vector2(position), 180., SMALL_HANDLE_LENGTH, 8);
        store.Push(diffraction_grating);
      }
      break; /* KEY DEBAG*/

    case sf::Keyboard::B:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): B" << std::endl;
      #endif 

      {
        DiffractionGrating diffraction_grating = DiffractionGrating(my_math::Vector2(position), 340., STANDART_HANDLE_LENGTH, 4);
        store.Push(diffraction_grating);
      }
      break; /* KEY DEBAG*/

    case sf::Keyboard::N:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): N" << std::endl;
      #endif 
      {
        DiffractionGrating diffraction_grating3 = DiffractionGrating(my_math::Vector2(position), 400., STANDART_HANDLE_LENGTH, 2);
        store.Push(diffraction_grating3);
      }
      break; /* KEY DEBAG*/

    case sf::Keyboard::M:
      #ifdef KEY_DEBUG
      std::cout << "HandleKey( ): M" << std::endl;
      #endif /* KEY DEBAG*/ 
      {
        DiffractionGrating diffraction_grating4 = DiffractionGrating(my_math::Vector2(position), 500.,
                                                                     STANDART_HANDLE_LENGTH, 1);
        store.Push(diffraction_grating4);
      }
      break;
  }
}

bool HandleDraw(sf::RenderWindow &window, Store &store) {
  #ifdef HANDLE_DRAW_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  store.Draw(window);

  #ifdef HANDLE_DRAW_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif

  return true;
}

bool HandleStore(Store &store)
{
  #ifdef HANDLE_STORE_TIMER
  std::chrono::high_resolution_clock::time_point debag_time_stamp = std::chrono::high_resolution_clock::now();
  #endif

  store.RemoveDistantWaves();
  store.MoveWaves();
  store.UpdateTime();

  #ifdef HANDLE_STORE_TIMER
  std::chrono::duration<float> debag_diff = std::chrono::high_resolution_clock::now() - debag_time_stamp;
  std::cout << debag_diff.count( ) << std::endl; 
  #endif
}

} // End of namespace handler.
