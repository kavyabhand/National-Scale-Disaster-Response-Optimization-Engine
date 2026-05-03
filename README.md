# National Scale Disaster Response Optimization Engine

## Overview

The National Scale Disaster Response Optimization Engine is a full-stack simulation system designed to model and analyze disaster scenarios using advanced data structures and algorithms. The system prioritizes disaster zones, allocates resources efficiently, and performs spatial and temporal analysis of affected regions.

The project combines a C++ backend engine with a Next.js frontend dashboard to visualize real-time analytics using a JSON-based data pipeline. Live earthquake data is pulled from the USGS feed via a Python script and fed into the C++ engine for processing.

---

## Features

### Backend (C++ Engine)
- Priority Queue (Max Heap) for disaster prioritization based on urgency score
- AVL Tree for maintaining sorted disaster analytics
- Quad Tree for spatial indexing of geographical regions
- Trie for fast region and name-based search
- Disjoint Set / Union Find for clustering connected disaster regions
- Interval Tree for temporal/range-based event lookups
- Segment Tree for cumulative range queries on regional metrics
- JSON export pipeline for frontend integration

### Live Data Ingestion (Python)
- `fetch_live_data.py` pulls real-time earthquake events from the USGS GeoJSON feed
- Normalizes events into the engine's input schema and writes `data/live_disasters.json`

### Frontend (Next.js Dashboard)
- Search and filter disaster regions
- Urgency filter controls
- Priority-based ranking table
- Urgency score visualization using bar charts
- Population impact analysis
- Interactive disaster map visualization

---

## System Architecture

The Python ingestion script fetches live disaster data, the C++ engine processes it through multiple data structures, and the results are exported as JSON for the Next.js dashboard to consume.

```

USGS Live Feed
        ↓
fetch_live_data.py
        ↓
data/live_disasters.json
        ↓
C++ Engine (main.cpp)
├── Priority Queue (Heap)
├── AVL Tree
├── Quad Tree
├── Trie
├── Disjoint Set / Union Find
├── Interval Tree
├── Segment Tree
        ↓
data/results.json
        ↓
frontend/public/data/results.json
        ↓
Next.js Frontend
├── Tables
├── Charts
├── Map Visualization

```

---

## Project Structure

```

project-root/
│
├── backend/
│   ├── main.cpp
│   ├── build.sh
│   ├── refresh_pipeline.sh
│   ├── fetch_live_data.py
│   ├── disaster                  # compiled engine binary
│   │
│   ├── models/
│   │   └── region.h
│   │
│   ├── structures/
│   │   ├── priority_queue.h
│   │   ├── avl_tree.h
│   │   ├── quad_tree.h
│   │   ├── trie.h
│   │   ├── disjoint_set.h
│   │   ├── interval_tree.h
│   │   ├── segment_tree.h
│   │   └── union_find.h
│   │
│   ├── utils/
│   │   └── sample_data.h
│   │
│   └── data/
│       ├── live_disasters.json
│       └── results.json
│
├── frontend/
│   ├── app/
│   │   ├── page.tsx
│   │   ├── layout.tsx
│   │   ├── globals.css
│   │   └── favicon.ico
│   ├── components/
│   │   └── DisasterMap.tsx
│   ├── public/
│   │   ├── data/results.json
│   │   ├── file.svg
│   │   ├── globe.svg
│   │   ├── next.svg
│   │   ├── vercel.svg
│   │   └── window.svg
│   ├── eslint.config.mjs
│   ├── next.config.ts
│   ├── postcss.config.mjs
│   ├── tsconfig.json
│   ├── package.json
│   ├── package-lock.json
│   ├── AGENTS.md
│   ├── CLAUDE.md
│   └── README.md
│
├── LICENSE
└── README.md

```

---

## How to Run

### Backend (C++ Engine)

Compile (uses `nlohmann/json` from Homebrew):
```bash
cd backend
g++ main.cpp -std=c++17 -I/opt/homebrew/opt/nlohmann-json/include -o disaster
```

Run:

```bash
./disaster
```

This generates the output file:

```
backend/data/results.json
```

---

### Build Script

```bash
cd backend
chmod +x build.sh
./build.sh
./disaster
```

---

### Live Data Ingestion

Install Python dependencies (in a virtualenv at `backend/venv`):

```bash
cd backend
python -m venv venv
source venv/bin/activate
pip install requests
```

Fetch live USGS earthquake data:

```bash
python fetch_live_data.py
```

This writes `backend/data/live_disasters.json`.

---

### Full Pipeline Execution

The `refresh_pipeline.sh` script activates the venv, fetches live data, runs the engine, and copies the results into the frontend's public directory:

```bash
cd backend
chmod +x refresh_pipeline.sh
./refresh_pipeline.sh
```

---

### Frontend (Next.js)

Install dependencies:

```bash
cd frontend
npm install
```

Run development server:

```bash
npm run dev
```

Open:

```
http://localhost:3000
```

---

## Data Flow

The system follows this pipeline:

USGS Feed → Python Fetcher → `live_disasters.json` → C++ Engine → Data Structure Processing → `results.json` → Next.js Frontend → Visualization Layer

---

## Core Data Structures Used

* **Priority Queue (Max Heap)** — disaster prioritization by urgency score
* **AVL Tree** — sorted ranking of regions
* **Quad Tree** — 2D spatial indexing of affected regions
* **Trie** — fast string-based region/name search
* **Disjoint Set** — clustering connected disaster regions
* **Union Find** — alternate clustering implementation for grouping events
* **Interval Tree** — temporal/range queries over event windows
* **Segment Tree** — range queries over regional metrics

---

## Output Format

Example JSON structure:

```json
{
  "total_regions": 5,
  "population_affected": 1200000,
  "priority_order": [
    {
      "name": "Region A",
      "population": 300000,
      "damage_level": 4,
      "urgency_score": 95,
      "latitude": 18.5,
      "longitude": 73.8
    }
  ]
}
```

---

## Future Improvements

* Real-time streaming updates using WebSockets
* Dijkstra-based emergency routing system
* Disaster propagation simulation using BFS
* Cloud deployment of backend engine
* Machine learning-based disaster prediction module

---

## Tech Stack

### Backend

* C++17
* STL
* Custom Data Structures
* nlohmann/json
* Python 3 (requests) for live data ingestion

### Frontend

* Next.js
* React
* TypeScript
* Recharts
* Tailwind CSS (via PostCSS)

---
