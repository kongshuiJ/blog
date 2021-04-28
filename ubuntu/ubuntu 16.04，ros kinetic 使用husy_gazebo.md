<p> <br />我当前使用的是ubuntu 16.04，ros kinetic ，Gazebo版本为7.0。protoc需要确保版本为2.6.1，而我当前的为3.4.0，因此需要将系统中的protoc替换为2.6.1版本。</p>
<p><br /> controller manager.:<br /> 	git https://github.com/ros-controls/ros_control.git (branch: kinetic-devel)</p>
<p>resource_retriever:<br />	git https://github.com/ros/resource_retriever.git (branch: kinetic-devel</p>
<p>LMS1xx:<br />	git https://github.com/clearpathrobotics/lms1xx.git (branch: master)</p>
<p>gazebo_ros:<br />	git https://github.com/ros-simulation/gazebo_ros_pkgs.git (branch: kinetic-devel)</p>
<p>control_toolbox:<br />	git https://github.com/ros-controls/control_toolbox.git (branch: kinetic-devel)</p>
<p>mrpt_bridge:<br />	 git https://github.com/mrpt-ros-pkg/mrpt_bridge.git (branch: master)</p>
<p>realtime_tools:<br />	git https://github.com/ros-controls/realtime_tools.git (branch: kinetic-devel)</p>
<p><br />转到catkin工作区的顶级目录，其中包含您要使用的ROS包的源代码。然后运行：<br />此命令可以神奇地安装catkin工作区中的软件包所依赖但在您的计算机上缺少的所有软件包。<br />sudo rosdep install --from-paths src --ignore-src -r -y --rosdistro kinetic</p>