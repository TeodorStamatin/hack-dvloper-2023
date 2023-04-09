import './App.css';

import { useState, useEffect } from "react";

import Chessboard from './components/Chessboard';
import History from './components/History';
import Chatbox from './components/Chatbox';

function App() {
  const [history, setHistory] = useState([]);

  const [data, setData] = useState([]);

  const [gameNumber, setGameNumber] = useState(0);
  const [gameInProgress, setGameInProgress] = useState(false);
  const [user, setUser] = useState("");
  const [loggedIn, setLoggedIn] = useState(false);
  const [usernameInput, setUsernameInput] = useState("");
  const [passwordInput, setPasswordInput] = useState("");
  const [loadInput, setLoadInput] = useState("");

  function startGame() {
    setGameInProgress(true);
    setGameNumber(gameNumber + 1);

    fetch("http://localhost:5000/api/createGame")
    .then(res => res.json())
    .then((data) => {console.log(data); setData(data.pieces); setGameNumber(data.game_id)});
  }

  function resignGame() {
    setGameInProgress(false);
  }

  function login() {
    fetch("http://localhost:5000/api/login", 
    {
      method: "POST",
      body: JSON.stringify(
        {
          username: usernameInput,
          password: passwordInput,
        }),
    }
  )
  .then(res => res.json())
  .then((data) => {
    if (data.status === "success") {
      setUser(data.username);
      setLoggedIn(true);
    }});
  }

  function logout() {
    fetch("http://localhost:5000/api/logout", 
    {
      method: "GET",
    }
  )
  .then(res => res.json())
  .then((data) => {
    if (data.status === "success") {
      setUser("");
      setLoggedIn(false);
    }});
  }

  function loadGame() {
    fetch("http://localhost:5000/api/loadGame", 
    {
      method: "POST",
      body: JSON.stringify(
        { game_id: loadInput }),
    })
    .then(res => res.json())
    .then((data) => {
      setHistory(data.history);
      console.log(history);
    });
  }

  return (
    <div className="App">
      <header className="App-header">
        <h1>The Black Sheep | Chess Engine</h1>
        { loggedIn ? <span>{`Hi, ${user}! Welcome among black sheep!`}<span className="logoutBtn" onClick={()=>logout()}>Logout</span></span>: 
        <div className="loginBox">
          <input type="text" placeholder="Username" value={usernameInput} onChange={(event) => setUsernameInput(event.target.value)} />  
          <input type="password" placeholder="Password" value={passwordInput} onChange={(event) => setPasswordInput(event.target.value)}/>
          <div className="loginBtnBox">
            <button className="loginBtn" onClick={() => login()}>Login</button>
            <button className="playAsGuestBtn">Play as guest</button>
          </div>
        </div>
        }
        {gameInProgress
        ? <div>
            <h2>Game: <span className="gameNumber">#{gameNumber}</span></h2>
            <div className="resignBtnBox">
              <button className="resignBtn" onClick={() => resignGame()}>Resign game</button>
            </div>
          </div>
        : ""}
        {user !== "" ?
        <div>
          { gameInProgress ? "" :
          <div className="playBtnBox">
            <button className="playBtn" onClick={() => startGame()}>Play with bot</button>
            <button className="playBtn" onClick={() => startGame()}>Play against Friend</button>
          </div>
          }
          <div className="btnBox">
            <input className="loadInput" placeholder='Game ID' value={loadInput} onChange={(event) => setLoadInput(event.target.value)}/>
            <button className="loadBtn" onClick={() => loadGame()}>Load game</button>
          </div>
        </div>
        : ""}
      </header>
      {gameInProgress
      ? <div className="App-body">
        <History history={history} setHistory={setHistory} />
        <Chessboard data={data} history={history} setHistory={setHistory} gameNumber={gameNumber} />
        <Chatbox userColor={"white"}/>
      </div>
      : ""
      }
    </div>
  );
}

export default App;
