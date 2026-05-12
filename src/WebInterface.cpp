#include "WebInterface.h"
#include <Arduino.h>

// ================================================================
//  WebInterface.cpp
// ================================================================

static const char HTML_REMOTE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<title>Samsung Remote</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;500;600&display=swap" rel="stylesheet">
<style>
  *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; -webkit-tap-highlight-color: transparent; }

  :root {
    --bg:        #09090b;
    --surface:   #141416;
    --btn:       #1c1c1f;
    --btn-hover: #252529;
    --btn-active:#2e2e33;
    --border:    #2a2a2f;
    --text:      #e4e4ec;
    --sub:       #6b6b80;
    --blue:      #3b82f6;
    --red:       #ef4444;
    --netflix:   #e50914;
    --green:     #22c55e;
    --radius-lg: 20px;
    --radius-md: 14px;
    --shadow:    0 2px 8px rgba(0,0,0,0.6);
  }

  body {
    background: var(--bg);
    font-family: 'Outfit', sans-serif;
    color: var(--text);
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 24px 16px 40px;
  }

  header {
    display: flex;
    align-items: center;
    gap: 10px;
    margin-bottom: 24px;
    opacity: 0;
    animation: fadeDown .5s ease forwards;
  }
  header .brand { font-size: 11px; font-weight: 600; letter-spacing: 4px; color: var(--sub); text-transform: uppercase; }
  header .dot   { width: 5px; height: 5px; background: var(--blue); border-radius: 50%; }
  header .name  { font-size: 11px; font-weight: 400; letter-spacing: 2px; color: var(--sub); text-transform: uppercase; }

  .remote {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 32px;
    padding: 24px 20px 32px;
    width: 100%;
    max-width: 300px;
    display: flex;
    flex-direction: column;
    gap: 12px;
    box-shadow: 0 32px 64px rgba(0,0,0,0.8), 0 0 0 1px rgba(255,255,255,0.03);
    opacity: 0;
    animation: fadeUp .6s .1s ease forwards;
  }

  .section { display: flex; flex-direction: column; gap: 8px; }
  .row     { display: flex; gap: 8px; }

  .btn {
    background: var(--btn);
    border: 1px solid var(--border);
    border-radius: var(--radius-md);
    color: var(--text);
    font-family: 'Outfit', sans-serif;
    font-size: 13px;
    font-weight: 500;
    cursor: pointer;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    gap: 4px;
    padding: 14px 8px;
    flex: 1;
    min-height: 54px;
    transition: background .12s, transform .08s, box-shadow .12s;
    box-shadow: var(--shadow);
    user-select: none;
  }
  .btn:hover  { background: var(--btn-hover); }
  .btn:active { background: var(--btn-active); transform: scale(.94); box-shadow: none; }
  .btn .icon  { font-size: 20px; line-height: 1; }
  .btn .label { font-size: 10px; color: var(--sub); letter-spacing: .5px; text-transform: uppercase; }

  .btn-power { background: rgba(239,68,68,.12); border-color: rgba(239,68,68,.25); color: var(--red); }
  .btn-power:hover  { background: rgba(239,68,68,.18); }
  .btn-power:active { background: rgba(239,68,68,.25); }

  .btn-netflix { background: rgba(229,9,20,.1); border-color: rgba(229,9,20,.2); color: var(--netflix); font-weight: 700; font-size: 14px; letter-spacing: 1px; }
  .btn-netflix:hover  { background: rgba(229,9,20,.16); }
  .btn-netflix:active { background: rgba(229,9,20,.22); }

  .btn-blue { background: rgba(59,130,246,.1); border-color: rgba(59,130,246,.2); color: var(--blue); }
  .btn-blue:hover  { background: rgba(59,130,246,.16); }
  .btn-blue:active { background: rgba(59,130,246,.22); }

  .btn-lg { min-height: 64px; font-size: 22px; border-radius: var(--radius-lg); }

  .power-row { display: flex; justify-content: center; }
  .btn-power-main { width: 72px; height: 72px; border-radius: 50%; font-size: 26px; flex: unset; min-height: unset; }

  .dpad { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 6px; align-items: center; }
  .dpad-center { display: flex; align-items: center; justify-content: center; }
  .btn-ok {
    width: 60px; height: 60px; border-radius: 50%;
    font-size: 13px; font-weight: 600; flex: unset; min-height: unset;
    color: var(--blue); border-color: rgba(59,130,246,.2); background: rgba(59,130,246,.08);
  }
  .btn-ok:hover  { background: rgba(59,130,246,.14); }
  .btn-ok:active { background: rgba(59,130,246,.2); }

  .divider { height: 1px; background: var(--border); margin: 2px 0; }

  .status {
    position: fixed;
    bottom: 24px; left: 50%;
    transform: translateX(-50%) translateY(60px);
    background: rgba(30,30,35,.95);
    border: 1px solid var(--border);
    border-radius: 40px;
    padding: 10px 20px;
    font-size: 13px; font-weight: 500;
    color: var(--text);
    backdrop-filter: blur(12px);
    transition: transform .3s cubic-bezier(.34,1.56,.64,1), opacity .3s;
    opacity: 0; white-space: nowrap; z-index: 99;
  }
  .status.ok   { color: var(--green); }
  .status.err  { color: var(--red); }
  .status.show { transform: translateX(-50%) translateY(0); opacity: 1; }

  @keyframes fadeDown { from { opacity:0; transform:translateY(-12px); } to { opacity:1; transform:translateY(0); } }
  @keyframes fadeUp   { from { opacity:0; transform:translateY(16px);  } to { opacity:1; transform:translateY(0); } }
  ::-webkit-scrollbar { display: none; }
</style>
</head>
<body>

<header>
  <span class="brand">Samsung</span>
  <span class="dot"></span>
  <span class="name">Crystal 58&Prime;</span>
</header>

<div class="remote">

  <div class="power-row">
    <button class="btn btn-power btn-power-main" onclick="cmd('power')">
      <span class="icon">⏻</span>
    </button>
  </div>

  <div class="divider"></div>

  <div class="section">
    <div class="row">
      <button class="btn btn-netflix btn-lg" onclick="cmd('netflix')">NETFLIX</button>
      <button class="btn btn-lg" onclick="cmd('prime')">
        <span class="icon">🎬</span>
        <span class="label">Prime</span>
      </button>
    </div>
    <div class="row">
      <button class="btn" onclick="cmd('home')">
        <span class="icon">⌂</span>
        <span class="label">SmartHub</span>
      </button>
      <button class="btn" onclick="cmd('back')">
        <span class="icon">↩</span>
        <span class="label">Voltar</span>
      </button>
    </div>
  </div>

  <div class="divider"></div>

  <div class="section">
    <div class="dpad">
      <div></div>
      <button class="btn" onclick="cmd('up')"><span class="icon">▲</span></button>
      <div></div>
      <button class="btn" onclick="cmd('left')"><span class="icon">◀</span></button>
      <div class="dpad-center">
        <button class="btn btn-ok" onclick="cmd('ok')">OK</button>
      </div>
      <button class="btn" onclick="cmd('right')"><span class="icon">▶</span></button>
      <div></div>
      <button class="btn" onclick="cmd('down')"><span class="icon">▼</span></button>
      <div></div>
    </div>
  </div>

  <div class="divider"></div>

  <div class="section">
    <div class="row">
      <button class="btn btn-blue" onclick="cmd('vol_up')">
        <span class="icon">🔊</span><span class="label">Vol +</span>
      </button>
      <button class="btn" onclick="cmd('ch_up')">
        <span class="icon">⬆</span><span class="label">Canal +</span>
      </button>
    </div>
    <div class="row">
      <button class="btn" onclick="cmd('mute')">
        <span class="icon">🔇</span><span class="label">Mudo</span>
      </button>
      <div style="flex:1"></div>
    </div>
    <div class="row">
      <button class="btn btn-blue" onclick="cmd('vol_down')">
        <span class="icon">🔉</span><span class="label">Vol -</span>
      </button>
      <button class="btn" onclick="cmd('ch_down')">
        <span class="icon">⬇</span><span class="label">Canal -</span>
      </button>
    </div>
  </div>

</div>

<div class="status" id="toast"></div>

<script>
  const toast = document.getElementById('toast');
  let toastTimer;

  function showToast(msg, tipo) {
    clearTimeout(toastTimer);
    toast.textContent = msg;
    toast.className   = 'status show ' + tipo;
    toastTimer = setTimeout(() => toast.className = 'status', 1800);
  }

  const labels = {
    power:'⏻ Power', vol_up:'🔊 Volume +', vol_down:'🔉 Volume -',
    mute:'🔇 Mudo', ch_up:'⬆ Canal +', ch_down:'⬇ Canal -',
    up:'▲ Cima', down:'▼ Baixo', left:'◀ Esquerda', right:'▶ Direita',
    ok:'✓ OK', back:'↩ Voltar', home:'⌂ SmartHub',
    netflix:'▶ Netflix', prime:'🎬 Prime Video',
  };

  async function cmd(comando) {
    if (navigator.vibrate) navigator.vibrate(30);
    try {
      const res  = await fetch('/ir?cmd=' + comando);
      const json = await res.json();
      showToast(json.ok ? (labels[comando] || comando) : 'Comando desconhecido', json.ok ? 'ok' : 'err');
    } catch (e) {
      showToast('Sem resposta do ESP32', 'err');
    }
  }
</script>
</body>
</html>
)=====";

// ================================================================

WebInterface::WebInterface(TVRemote& remote, uint16_t porta)
  : _server(porta), _remote(remote) {}

void WebInterface::begin() {
  _rotasSetup();
  _server.begin();
  Serial.println("[Web] Servidor iniciado na porta 80.");
}

void WebInterface::_rotasSetup() {
  _server.on("/", HTTP_GET, [](AsyncWebServerRequest* req) {
   req->send(200, "text/html", HTML_REMOTE);
  });

  _server.on("/ir", HTTP_GET, [this](AsyncWebServerRequest* req) {
    if (!req->hasParam("cmd")) {
      _responderErro(req, "parametro 'cmd' ausente");
      return;
    }
    String comando = req->getParam("cmd")->value();
    _remote.enviar(comando) ? _responderOk(req) : _responderErro(req, "comando desconhecido: " + comando);
  });

  _server.onNotFound([this](AsyncWebServerRequest* req) {
    _responderErro(req, "rota nao encontrada");
  });
}

void WebInterface::_responderOk(AsyncWebServerRequest* req) {
  req->send(200, "application/json", "{\"ok\":true}");
}

void WebInterface::_responderErro(AsyncWebServerRequest* req, const String& msg) {
  req->send(400, "application/json", "{\"ok\":false,\"erro\":\"" + msg + "\"}");
}
