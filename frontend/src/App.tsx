import { useState } from 'react'
import './App.css'
import axios, { AxiosResponse } from 'axios';

function App() {
  const [state, setState] = useState<boolean>(false);

  const handleClick = async () => {
    try {
      const response: AxiosResponse = await axios.get(`http://127.0.0.1:8000/led/${state ? "OFF" : "ON"}`)
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
    setState(!state);
  }

  return (
    <>
      <h1>Click the Button to On or Off the LED</h1>
      <div className="card">
        <button onClick={handleClick}>
          Turn LED {state ? "OFF" : "ON"}
        </button>
        <h3 style={state ? { color: "green" } : { color: "red" }}>
          LED is currently {state ? "ON" : "OFF"}
        </h3>
      </div>
    </>
  )
}

export default App
