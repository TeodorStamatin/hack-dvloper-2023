import './App.css';

import { useState } from "react";

import Chessboard from './components/Chessboard';
import History from './components/History';
import Chatbox from './components/Chatbox';

function App() {
  const [history, setHistory] = useState([]);

  const [gameNumber, setGameNumber] = useState(0);
  const [gameInProgress, setGameInProgress] = useState(false);

  function startGame() {
    setGameInProgress(true);
    setGameNumber(gameNumber + 1);
  }

  function resignGame() {
    setGameInProgress(false);
  }

  return (
    <div className="App">
      <header className="App-header">
        <h1>The Black Sheep | Chess Engine</h1>
        {gameInProgress 
        ? <div>
            <h2>Game: <span className="gameNumber">#{gameNumber}</span></h2>
            <div className="resignBtnBox">
              <button className="resignBtn" onClick={() => resignGame()}>Resign game</button>
            </div>
          </div>
        : <div className="playBtnBox">
            <button className="playBtn" onClick={() => startGame()}>Play with bot</button>
            <button className="playBtn" onClick={() => startGame()}>Play against Friend</button>
          </div>}
        <div className="btnBox">
          {history.length > 0 ? <button className="saveBtn">Save game</button> : ""}
          <button className="loadBtn">Load game</button>
        </div>
      </header>
      {gameInProgress
      ? <div className="App-body">
        <History history={history} setHistory={setHistory} />
        <Chessboard history={history} setHistory={setHistory} />
        <Chatbox userColor={"white"}/>
      </div>
      : ""
      }
    </div>
  );
}

export default App;
