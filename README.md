# A 3D Simulation Framework with Ray-Tracing Propagation for LoRaWAN Communication

[![DOI](https://zenodo.org/badge/685559585.svg)](https://zenodo.org/badge/latestdoi/685559585)


### Citations

Pending publication (Already accepted). Soon.

### Abstract

Introducing a robust simulation framework designed for accurately modeling the performance of LoRaWAN communication technology in various IoT deployments. This tool uniquely integrates a network simulator, a 3D engine, and a ray-tracing tool, providing a realistic representation of network scenarios, especially in complex urban environments. When compared to traditional models like Okumura-Hata, our framework, utilizing open geographical information system data, demonstrated a notable improvement in signal strength estimation accuracy in challenging urban contexts, as validated through [experimental campaigns](https://github.com/girtel/Res_3DLoRaSimulator/tree/main) in Cartagena, Spain.

### Simulation process
<div align="center">
<img src="https://github.com/girtel/3DLoRaSimulator/assets/40019177/59a3ced7-cd84-49b8-b9db-1a83c8bf9a7d" width="50%"/>
</div>

### Simulation results

Simulation results as coverage map

<table>
<tbody>
  <tr>
    <td>Tester coverage</td>
    <td>Ray-Tracing coverage simulations</td>
  </tr>
  <tr>
    <td><img src="https://github.com/girtel/3DLoRaSimulator/assets/40019177/00070a13-c384-4ba9-82f9-7c5a243d2724"></td>
    <td><img src="https://github.com/girtel/3DLoRaSimulator/assets/40019177/40f36b69-89d9-4756-9f58-ec2f865b2587"></td>
  </tr>
  <tr>
    <td>Log-Distance coverage simulations</td>
    <td>Okumura-Hata coverage simulations</td>
  </tr>
  <tr>
    <td><img src="https://github.com/girtel/3DLoRaSimulator/assets/40019177/320a7c3e-ba8d-49db-836b-1192138a77bf"></td>
    <td><img src="https://github.com/girtel/3DLoRaSimulator/assets/40019177/c47729f3-8505-447a-b02e-6f7696bceede"></td>
  </tr>
</tbody>
</table>


### Requirements

- OMNeT++ 6.0.1:
  - Linux: https://github.com/omnetpp/omnetpp/releases/download/omnetpp-6.0.1/omnetpp-6.0.1-linux-x86_64.tgz
  - Windows: https://github.com/omnetpp/omnetpp/releases/download/omnetpp-6.0.1/omnetpp-6.0.1-windows-x86_64.zip
  - Core: https://github.com/omnetpp/omnetpp/releases/download/omnetpp-6.0.1/omnetpp-6.0.1-core.tgz
- Cuda 10.2: https://developer.nvidia.com/cuda-10.2-download-archive
- OptiX 6.5: https://developer.nvidia.com/designworks/optix/downloads/6.5.0/linux64
- Opal: https://gitlab.com/esteban.egea/opal (Software outdated)
- Veneris: https://gitlab.com/esteban.egea/veneris (To create the 3D environment)

### Installation

Download this repository and open it as a project with OMNeT++ 6.0.1. Install Opal.

Go to `Project` > `Project Features` > `C/C++ General` > `Paths and Symbols`
- `Includes` > `GNU C++`
  - */cuda10.2/include
  - */optix6.5/SDK/opal
  - */optix6.5/include
- `Libraries`
  - */x86_64-linux-gnu/libboost_system.so
  - */cuda10.2/lib64/libcudart.so
  - */optix6.5/lib64/liboptix.so
  - */optix6.5/lib64/liboptixu.so
  - */optix6.5/SDK/lib64/libopal_s.so
- `Library Paths`
  - */cuda10.2/lib64
  - */optix6.5/SDK/lib
  - */optix6.5/lib64
