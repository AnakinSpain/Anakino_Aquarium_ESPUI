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
   
    auto tab1 = ESPUI.addControl(Tab, "", "Status");
    
    // grupo de datos
    aguatempId =
    ESPUI.addControl(Label, "Agua ºC ", "", ControlColor::Alizarin, tab1); // temp agua
    
    // card de hora
    realtime_LabelId= ESPUI.addControl(Label,"HORA:","", ControlColor::Emerald, tab1);

    // group switchers. AQUI IRA EL ESTADO DE LOS RELES   
  auto gruposreles = 
  ESPUI.addControl(Switcher, "Estados RELES", "0", Dark, tab1, generalCallback);
  Switch_2 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);// aireador
  Switch_3 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);//calentador
  Switch_4 = ESPUI.addControl(Switcher, "", "", Sunflower, gruposreles, generalCallback);//led
  
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "", None, gruposreles), clearLabelStyle);
  //We will now need another label style. This one sets its width to the same as a switcher (and turns off the background)
  String switcherLabelStyle = "width: 60px; margin-left: .3rem; margin-right: .3rem; background-color: unset;";
  //We can now just add the styled labels.
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "AIR", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "2", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "HEAT", None, gruposreles), switcherLabelStyle);
  ESPUI.setElementStyle(ESPUI.addControl(Label, "", "LED", None, gruposreles), switcherLabelStyle);

  /*
   * Tab: PARÁMETROS
   * This tab contains all the basic ESPUI controls, and shows how to read and update them at runtime.
   *-----------------------------------------------------------------------------------------------------------*/
    auto tab2 = ESPUI.addControl(Tab, "", "Parámetros");
        
    //MODO FUNCIONAMIENTO LUZ
    //so that the storage is allocated in global memory and not just on the stack of this function.)
     static String optionValues[] {"Modo AUTO", "MODO ON", "MODO OFF"};
    auto mainselector_luz = ESPUI.addControl(Select, "Modo Luz", "", Wetasphalt, tab2, generalCallback);
    for(auto const& v : optionValues) {
    ESPUI.addControl(Option, v.c_str(), v, None, mainselector_luz);
  }
   // INTRODUCCION HORA ENCENDIDA/APAGADA
    text_time1 = ESPUI.addControl(Text, "Luz", luz_on_temp, Turquoise, tab2, generalCallback); // INPUT ON DEL PRIMER TIMER
    ESPUI.setInputType(text_time1, "time");
    text_time2 = ESPUI.addControl(Text,"OFF", luz_off_temp, Turquoise, text_time1, generalCallback); // INPUT OFF DEL PRIMER TIMER
    ESPUI.setInputType(text_time2, "time");

    // INPUT para la temperatura del agua Number inputs also accept Min and Max components, but you should still validate the values.
    mainNumber = ESPUI.addControl(Number, "Temperatura agua deseada", "24", Emerald, tab2, generalCallback);
    ESPUI.addControl(Min, "", "20", None, mainNumber);
    ESPUI.addControl(Max, "", "30", None, mainNumber);

  


    // BOTON GRABAR EN EEPROM
    button1 = ESPUI.addControl(ControlType::Button, "GRABAR", "Press", ControlColor::Peterriver, tab2, &boton1_Callback);

    ESPUI.addControl(Separator, "Más opciones", "", None, tab2);
   button2 = ESPUI.addControl(ControlType::Button, "RESTART ESP32", "Press", ControlColor::Peterriver, tab2, &boton2_Callback);

    
  /*
   * Tab: WiFi Credentials
   * You use this tab to enter the SSID and password of a wifi network to autoconnect to.
   *-----------------------------------------------------------------------------------------------------------*/
  auto wifitab = ESPUI.addControl(Tab, "", "WiFi Credentials");
  wifi_ssid_text = ESPUI.addControl(Text, "SSID", "", Alizarin, wifitab, textCallback);
  //Note that adding a "Max" control to a text control sets the max length
  ESPUI.addControl(Max, "", "32", None, wifi_ssid_text);
  wifi_pass_text = ESPUI.addControl(Text, "Password", "", Alizarin, wifitab, textCallback);
  ESPUI.addControl(Max, "", "64", None, wifi_pass_text);
  ESPUI.addControl(Button, "Save", "Save", Peterriver, wifitab, enterWifiDetailsCallback);

  
/*
    uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "Ajustes 1", "Ajustes 1");
    uint16_t tab2 = ESPUI.addControl(ControlType::Tab, "Ajustes 2", "Ajustes 2");
    uint16_t tab3 = ESPUI.addControl(ControlType::Tab, "Ajustes 3", "Ajustes 3");

////// TAB 1
    
    button1 = ESPUI.addControl(ControlType::Button, "Push Button", "Press", ControlColor::Peterriver, tab1, &buttonCallback);
    ESPUI.addControl(ControlType::Slider, "Slider one", "30", ControlColor::Alizarin, tab1, &slider);
//  ESPUI.addControl(ControlType::Button, "Other Button", "Press", ControlColor::Wetasphalt, tab1, &buttonExample, (void*)19);

////// TAB 2
    ESPUI.addControl(ControlType::PadWithCenter, "Pad with center", "", ControlColor::Sunflower, tab2, &padExample);

    ////// TAB 3
    ESPUI.addControl(ControlType::Pad, "Pad without center", "", ControlColor::Carrot, tab3, &padExample);
//    switchOne = ESPUI.addControl(ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, tab3, &switchExample);
    ESPUI.addControl(ControlType::Switcher, "Switch two", "", ControlColor::None, tab3, &otherSwitchExample);
    ESPUI.addControl(ControlType::Slider, "Slider two", "100", ControlColor::Alizarin, tab3, &slider);
    ESPUI.addControl(ControlType::Number, "Number:", "50", ControlColor::Alizarin, tab3, &numberCall);

    /*
     * .begin loads and serves all files from PROGMEM directly.
     * If you want to serve the files from LITTLEFS use ESPUI.beginLITTLEFS
     * (.prepareFileSystem has to be run in an empty sketch before)
     */

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
