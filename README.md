# National Scale Disaster Response Optimization Engine

## Overview

The National Scale Disaster Response Optimization Engine is a full-stack simulation system designed to model and analyze disaster scenarios using advanced data structures and algorithms. The system prioritizes disaster zones, allocates resources efficiently, and performs spatial and temporal analysis of affected regions.

The project combines a C++ backend engine with a Next.js frontend dashboard to visualize real-time analytics using a JSON-based data pipeline.

---

## Features

### Backend (C++ Engine)
- Priority Queue (Max Heap) for disaster prioritization based on urgency score
- AVL Tree for maintaining sorted disaster analytics
- Quad Tree for spatial indexing of geographical regions
- Trie for fast region and name-based search
- JSON export pipeline for frontend integration

### Frontend (Next.js Dashboard)
- Search and filter disaster regions
- Priority-based ranking table
- Urgency score visualization using bar charts
- Population impact analysis
- Interactive disaster map visualization

---

## System Architecture

C++ Engine processes raw disaster data using multiple data structures. The processed results are exported as JSON and consumed by the frontend dashboard for visualization and analysis.

```

Sample Data
↓
C++ Engine
├── Priority Queue (Heap)
├── AVL Tree
├── Quad Tree
├── Trie
↓
results.json
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
├── main.cpp
├── build.sh
├── refresh_pipeline.sh
│
├── models/
│   └── region.h
│
├── structures/
│   ├── priority_queue.h
│   ├── avl_tree.h
│   ├── quad_tree.h
│   ├── trie.h
│
├── utils/
│   └── sample_data.h
│
├── data/
│   └── results.json
│
└── frontend/
├── app/page.tsx
├── components/DisasterMap.tsx
├── tailwind.config.js

````

---

## How to Run

### Backend (C++ Engine)

Compile:
```bash
g++ -std=c++17 main.cpp -o engine
````

Run:

```bash
./engine
```

This generates the output file:

```
data/results.json
```

---

### Build Script

```bash
chmod +x build.sh
./build.sh
./engine
```

---

### Full Pipeline Execution

```bash
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

C++ Engine → Data Structures Processing → JSON Output → Next.js Frontend → Visualization Layer

---

## Core Data Structures Used

* Priority Queue (Max Heap): disaster prioritization
* AVL Tree: sorted ranking of regions
* Quad Tree: spatial indexing
* Trie: fast string-based search

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

### Frontend

* Next.js
* React
* Recharts
* Tailwind CSS

---

