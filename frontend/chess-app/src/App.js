import './App.css';

import { useState } from "react";

import Chessboard from './components/Chessboard';
import History from './components/History';
import Chatbox from './components/Chatbox';

function App() {
  const [history, setHistory] = useState([
    {pieceType: "WHITE_PAWN", from: "A1", to: "A2"},
  ]);

  return (
    <div className="App">
      <header className="App-header">
        <h1>The Black Sheep | Chess Engine</h1>
      </header>
      <div className="App-body">
        <History history={history} setHistory={setHistory} />
        <Chessboard history={history} setHistory={setHistory} />
        <Chatbox userId={1}/>
      </div>
    </div>
  );
}

export default App;
