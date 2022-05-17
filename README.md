BSP map builder

  What is it?
  -----------
  
  My first game project using the sfml library and OpenGL.
  Based on a simple top-down race. I found it uninteresting 
  to constantly use the same maps and I created a map generator 
  based on Binary space partitioning and vector math.
  
 
  Basic Functions
  -----------
  
  The generator has three methods of space division: 
  1. StepByStep where a consecutive clockwise division of the field is used
  
  ![SbS2](https://user-images.githubusercontent.com/105053896/168847708-cbe0f396-7b8b-468e-be9d-82ba34b69e0f.gif)

  2. Regresion where we divide the largest piece of the field 
  
  ![L_S](https://user-images.githubusercontent.com/105053896/168847426-24b0ac8b-3a64-4b72-bd30-d6ff08c73352.gif)
  
  3. Cubic where we use a сubic division method
  
  ![Cubic](https://user-images.githubusercontent.com/105053896/168847903-1686f2d6-450b-4d24-b717-42b3fb2f6416.gif)

  After that we use the field sorting method to build the point topology
  ![Sort](https://user-images.githubusercontent.com/105053896/168849046-ab84a91b-8b82-4240-b1d5-20dc58c5c13e.gif)


  Based on the given topology, we construct Bézier curves, 
  and then by determining the polarity of the obtained angles 
  (finding the sign area   ![image](https://user-images.githubusercontent.com/105053896/168850735-42eb5ffd-2a8f-4287-9e3b-dd70bc4300b3.png)) 
  we scale and create another topology with a smaller scale. 
  
  ![Splines](https://user-images.githubusercontent.com/105053896/168851856-eace20ed-5e9e-4479-90b1-1e66c856eb93.gif)
  
  We can use this data to create interesting and unrepeatable maps for our racing game (｡◕‿◕｡) 

  
