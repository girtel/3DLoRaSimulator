# A 3D Simulation Framework with Ray-Tracing Propagation for LoRaWAN Communication

[![DOI](https://zenodo.org/badge/685559585.svg)](https://zenodo.org/badge/latestdoi/685559585)


### Citations

[In Press, Journal Pre-proof.](https://doi.org/10.1016/j.iot.2023.100964)

```
@article{RUZNIETO2023100964,
title = {A 3D simulation framework with ray-tracing propagation for LoRaWAN communication},
journal = {Internet of Things},
pages = {100964},
year = {2023},
issn = {2542-6605},
doi = {https://doi.org/10.1016/j.iot.2023.100964},
url = {https://www.sciencedirect.com/science/article/pii/S2542660523002871},
author = {Andres Ruz-Nieto and Esteban Egea-Lopez and José-María Molina-García-Pardo and Jose Santa},
keywords = {LoRaWAN, IoT, Simulation, Ray-tracing, LP-WAN},
abstract = {The adoption of Low-Power Wide-Area Networks (LP-WAN) for interconnecting remote wireless sensors has become a reality in smart scenarios, covering communications needs of large Internet of Things (IoT) deployments. The correct operation and expected performance of such network scenarios, which can range hundreds or thousands of nodes and tens of squared kilometres, should be assessed before carrying out the deployment to save installation and maintenance costs. Common network planning tools can help to roughly study potential coverage, but network simulation offers fine-grained information about network performance. Nevertheless, current simulation frameworks include limited propagation models based on statistical and empirical measurements that do not consider scenario particularities, such as terrain elevation, buildings or vegetation. This is critical in urban settings. In this line, this paper presents a simulation framework including a network simulator, a 3D engine and a ray-tracing tool, which models realistically the performance of Long-Range Wide-Area Network (LoRaWAN) communication technology. We have evaluated the performance of the solution taking as reference experimental campaigns in the city of Cartagena (Spain), comparing data obtained when simulating with the commonly employed propagation models such as Okumura-Hata or path loss. Results indicate that our framework, set-up with data from open geographical information systems, accurately fits experimental values, reporting improvements between 10% and 50% in the error committed when estimating signal strength in challenging urban streets with signal obstruction, as compared with the better performing classical model, Okumura-Hata.}
}
```

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
- Unity 2017.3.030f: https://download.unity3d.com/download_unity/b84f5794ed91/UnityDownloadAssistant-2017.3.0f1.exe

### Create 3D environment (Spain)
To create the 3D environment you should install [QGIS](https://www.qgis.org/es/site/) w/[Spanish Inspire Catastral Downloader](https://plugins.qgis.org/plugins/Spanish_Inspire_Catastral_Downloader/), [dem2mesh](https://github.com/OpenDroneMap/dem2mesh) and [MeshLab](https://www.meshlab.net/)

1. Terrain model
	1. Go to [CNIG](https://centrodedescargas.cnig.es/CentroDescargas/index.jsp), select "MODELOS DIGITALES DEL TERRENO" and inside it select MTD02. After that you can download the zone where you want simulate.
 	2. Open the files in QGIS and crop the zone that you want to generate. Save it on GeoTIF format.
 	3. With dem2mesh convert this TIF image to PLY and with MeshLab you can open the PLY file, process the 3D environment (if needed) and export it to OBJ file.
2. City model
	1. With "Spanish Inspire Catastral Downloader" in QGIS you can download the different zones of Spanish Cadastre, select the zone that you want to simulate and download it. After that you need to crop the zone that you want to generate (usually the same that in Terrain Model).
 2. Execute the Python script (not available yet) on QGIS to generate q JSON file.

3.  JSON OMNeT generation
	1. Open Unity and import veneris package.
	2. Load Terrain Model.
 	3. Click on `Veneris` > `Load SUMO Network in Editor` and click on `SumoBuilderOnEditor`.
  4. Select `Use custom JSON` and add JSON file cliking on `Select polygons file`. After click on `Create EnvironmentBuilder`.
  5. Go to `SumoEnvironmentBuilderOnEditor` and click on `Build Environment`.
  6. When the process finish, align Terrain Model with City Model (are usually small adjustments).
  7. Finally you can save the scenario on `Opal` > `File` > `Save Scenario as JSON`

### Installation

Download this repository and open it as a project with OMNeT++ 6.0.1. Install Opal.

Go to `Project` > `Project Features` > `C/C++ General` > `Paths and Symbols`
- `Includes` > `GNU C++`
  - `*/cuda10.2/include`
  - `*/optix6.5/SDK/opal`
  - `*/optix6.5/include`
- `Libraries`
  - `*/x86_64-linux-gnu/libboost_system.so`
  - `*/cuda10.2/lib64/libcudart.so`
  - `*/optix6.5/lib64/liboptix.so`
  - `*/optix6.5/lib64/liboptixu.so`
  - `*/optix6.5/SDK/lib64/libopal_s.so`
- `Library Paths`
  - `*/cuda10.2/lib64`
  - `*/optix6.5/SDK/lib`
  - `*/optix6.5/lib64`
