void setupUI(){
  ///////////////////////////////////////////////////////////

     /////////////////////////////////////
    ///////////////             /////////
   //////////////// PESTAÑAS    ////////
  /////////////////             ///////
 /////////////////////////////////////

  String clearLabelStyle = "background-color: unset; width: 100%;";
  
  /*
   * Tab: STATUS
   * This tab contains all the basic ESPUI controls, and shows how to read and update them at runtime.
   *-----------------------------------------------------------------------------------------------------------*/
   
    auto status_tab = ESPUI.addControl(Tab, "", "Status");
    
    // grupo de datos
    aguatempId =
    ESPUI.addControl(Label, "Agua ºC ", "", ControlColor::Alizarin, status_tab); // temp agua
    
    // card de hora
    realtime_LabelId= ESPUI.addControl(Label,"Hora:","", ControlColor::Emerald, status_tab);

    // group switchers. AQUI IRA EL ESTADO DE LOS RELES   
  auto gruposreles = 
  ESPUI.addControl(Switcher, "Estados RELES", "0", Dark, status_tab, generalCallback);
  Switch_2 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);// aireador
  Switch_3 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);//calentador
  Switch_4 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);//led
  
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "", None, gruposreles), clearLabelStyle);
  //We will now need another label style. This one sets its width to the same as a switcher (and turns off the background)
  String switcherLabelStyle = "width: 60px; margin-left: .3rem; margin-right: .3rem; background-color: unset;";
  //We can now just add the styled labels.
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "1", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "AIR", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "HEAT", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "LED", None, gruposreles), switcherLabelStyle);

  // grupo de datos
    RSSItempId = ESPUI.addControl(Label, "Señal RSSI: ", "", ControlColor::Alizarin, status_tab); // RSSI

    
  /*
   * Tab: PARÁMETROS
   * This tab contains all the basic ESPUI controls, and shows how to read and update them at runtime.
   *-----------------------------------------------------------------------------------------------------------*/
    auto param_tab = ESPUI.addControl(Tab, "", "Parámetros");
        
    //MODO FUNCIONAMIENTO LUZ
  uint16_t select1
        = ESPUI.addControl(ControlType::Select, "Modo Luz:", "", ControlColor::Alizarin, param_tab, &selectCall);
    ESPUI.addControl(ControlType::Option, "MODO AUTO", "MODO AUTO", ControlColor::Alizarin, select1);
    ESPUI.addControl(ControlType::Option, "MODO ON", "MODO ON", ControlColor::Alizarin, select1);
    ESPUI.addControl(ControlType::Option, "MODO OFF", "MODO OFF", ControlColor::Alizarin, select1);
    
   // INTRODUCCION HORA ENCENDIDA/APAGADA
    text_time1 = ESPUI.addControl(Text, "Luz", luz_on_temp, Turquoise, param_tab, luz_on_Callback); // INPUT ON DEL PRIMER TIMER
    ESPUI.setInputType(text_time1, "time");
    text_time2 = ESPUI.addControl(Text,"OFF", luz_off_temp, Turquoise, text_time1, luz_off_Callback); // INPUT OFF DEL PRIMER TIMER
    ESPUI.setInputType(text_time2, "time");

    // INPUT para la temperatura del agua Number inputs also accept Min and Max components, but you should still validate the values.
    mainNumber = ESPUI.addControl(Number, "Temperatura agua deseada", "24", Emerald, param_tab, temperatura_Callback);
    ESPUI.addControl(Min, "", "20", None, mainNumber);
    ESPUI.addControl(Max, "", "30", None, mainNumber);

    // BOTON GRABAR EN EEPROM
    boton_param = ESPUI.addControl(ControlType::Button, "GRABAR", "Press", ControlColor::Peterriver, param_tab, &boton_param_Callback);

  /*
   * Tab: aireador
   * You use this tab to enter the SSID and password of a wifi network to autoconnect to.
   *-----------------------------------------------------------------------------------------------------------*/
  auto aire_tab = ESPUI.addControl(Tab, "", "Aireador");

      //MODO AIREADOR
      
  uint16_t select2
        = ESPUI.addControl(ControlType::Select, "Modo Aireador:", "", ControlColor::Alizarin, aire_tab, &selectCall_2);
    ESPUI.addControl(ControlType::Option, "MODO AUTO", "MODO AUTO", ControlColor::Alizarin, select2);
    ESPUI.addControl(ControlType::Option, "MODO ON", "MODO ON", ControlColor::Alizarin, select2);
    ESPUI.addControl(ControlType::Option, "MODO OFF", "MODO OFF", ControlColor::Alizarin, select2);
    
   // INTRODUCCION HORA ENCENDIDA/APAGADA
    text_time_ai1 = ESPUI.addControl(Text, "Hora Aireador", ai_on_temp, Turquoise, aire_tab, ai_on_Callback); // INPUT ON DEL PRIMER TIMER
    ESPUI.setInputType(text_time_ai1, "time");
    text_time_ai2 = ESPUI.addControl(Text,"OFF", ai_off_temp, Turquoise, text_time_ai1, ai_off_Callback); // INPUT OFF DEL PRIMER TIMER
    ESPUI.setInputType(text_time_ai2, "time");
    
    // BOTON GRABAR EN EEPROM
    boton_aire = ESPUI.addControl(ControlType::Button, "GRABAR", "Press", ControlColor::Peterriver, aire_tab, &boton_aire_Callback);
  
  /*
   * Tab: RESET
   * Pestaña para grabar o reiniciar el ESP32
   *-----------------------------------------------------------------------------------------------------------*/
    auto reset_tab = ESPUI.addControl(Tab, "", "Reset");
    boton_restart = ESPUI.addControl(ControlType::Button, "RESTART ESP32", "Press", ControlColor::Peterriver, reset_tab, &boton_restart_Callback);
         
  /*
   * Tab: CONFIGURACION
   * You use this tab to enter the SSID and password of a wifi network to autoconnect to.
   *-----------------------------------------------------------------------------------------------------------*/
  auto config_tab = ESPUI.addControl(Tab, "", "Configuracion");
  wifi_ssid_text = ESPUI.addControl(Text, "SSID", "", Alizarin, config_tab, textCallback);
  //Note that adding a "Max" control to a text control sets the max length
  ESPUI.addControl(Max, "", "32", None, wifi_ssid_text);
  wifi_pass_text = ESPUI.addControl(Text, "Password", "", Alizarin, config_tab, textCallback);
  ESPUI.addControl(Max, "", "64", None, wifi_pass_text);
  ESPUI.addControl(Button, "Guardar", "Guardar", Peterriver, config_tab, enterWifiDetailsCallback);
  ESPUI.addControl(ControlType::Separator, "Actualizar firmware", "", ControlColor::None, config_tab);

  // BOTON COMPROBAR VERSION
    boton_ver = ESPUI.addControl(ControlType::Button, "Actualizar firm", "Press", ControlColor::Peterriver, config_tab, &boton_ver_Callback);


    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    /*
     * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
     * SECURE way of limiting access.
     * Anyone who is able to sniff traffic will be able to intercept your password
     * since it is transmitted in cleartext. Just add a string as username and
     * password, for example begin("ESPUI Control", "username", "password")
     */   
}
