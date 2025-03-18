import { useState } from 'react'
import './App.css'
import axios, { AxiosResponse } from 'axios';

function App() {
  // for all the leds (5 only)
  const [allLightState, setAllLightState] = useState<boolean>(false);

  // for each led
  const [light1State, setLight1State] = useState<boolean>(false);
  const [light2State, setLight2State] = useState<boolean>(false);
  const [light3State, setLight3State] = useState<boolean>(false);
  const [light4State, setLight4State] = useState<boolean>(false);
  const [light5State, setLight5State] = useState<boolean>(false);

  // pattern state
  const [pattern, setPattern] = useState<boolean>(false);

  const handleSingleLedRequest = async (state: boolean, led: number): Promise<void> => {
    try {
      const response: AxiosResponse = await axios.get(`http://127.0.0.1:8000/led/${led}/${state ? "OFF" : "ON"}`)
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  }

  const handleSingleLed = async (led: number): Promise<void> => {
    switch (led) {
      case 1:
        handleSingleLedRequest(light1State, led);
        setLight1State(!light1State);
        break;
      case 2:
        handleSingleLedRequest(light2State, led);
        setLight2State(!light2State);
        break;
      case 3:
        handleSingleLedRequest(light3State, led);
        setLight3State(!light3State);
        break;
      case 4:
        handleSingleLedRequest(light4State, led);
        setLight4State(!light4State);
        break;
      case 5:
        handleSingleLedRequest(light5State, led);
        setLight5State(!light5State);
        break;
      default:
        break;
    }
  }

  const handleAllLeds = async (): Promise<void> => {
    try {
      const response: AxiosResponse = await axios.get(`http://127.0.0.1:8000/led/all/${allLightState ? "OFF" : "ON"}`);
      if (response) {
        console.log(response.data);
      }
    } catch (error) {
      console.error(error);
    }
    setAllLightState(!allLightState);
  }

  const handlePattern = async (): Promise<void> => {
    try {
      const response: AxiosResponse = await axios.get(`http://127.0.0.1:8000/led/pattern/${pattern ? "OFF" : "ON"}`);
      if (response) {
        console.log(response.data);
      }
    } catch (error) {
      console.error(error);
    }
    setPattern(!pattern);
  }

  return (
    <>
      <h1>LED Controller</h1>
      <div className="card">
        <div>
          <button onClick={handleAllLeds}>
            All LEDs {allLightState ? 'ON' : 'OFF'}
          </button>
        </div><br />
        <div>
          <button onClick={handlePattern}>
            Pattern {pattern ? 'ON' : 'OFF'}
          </button>
        </div><br />
        <div>
          <button onClick={() => handleSingleLed(1)}>Light 1: {light1State ? "ON" : "OFF"}</button>
          <button onClick={() => handleSingleLed(2)}>Light 2: {light2State ? "ON" : "OFF"}</button>
          <button onClick={() => handleSingleLed(3)}>Light 3: {light3State ? "ON" : "OFF"}</button>
          <button onClick={() => handleSingleLed(4)}>Light 4: {light4State ? "ON" : "OFF"}</button>
          <button onClick={() => handleSingleLed(5)}>Light 5: {light5State ? "ON" : "OFF"}</button>
        </div>
      </div>
    </>
  )
}

export default App
