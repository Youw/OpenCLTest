
#include <CL/cl.h>

#include <iostream>
#include <string>
#include <vector>

std::string platformInfoStr(cl_platform_id platform_id, cl_platform_info param)
{
	size_t param_size = 0;
	clGetPlatformInfo(platform_id, param, 0, nullptr, &param_size);
	std::string info(param_size, '\0');
	clGetPlatformInfo(platform_id, param, param_size, &info[0], 0);

	if (info[param_size - 1] == '\0')
		info.resize(param_size - 1);

	return info;
}

std::string deviceInfoStr(cl_device_id device_id, cl_device_info param)
{
	size_t param_size = 0;
	clGetDeviceInfo(device_id, param, 0, nullptr, &param_size);
	std::string info(param_size, '\0');
	clGetDeviceInfo(device_id, param, param_size, &info[0], 0);

	if (info[param_size - 1] == '\0')
		info.resize(param_size - 1);

	return info;
}

void printInfo(cl_device_id device_id)
{
	std::cout << '\t' 
		<< deviceInfoStr(device_id, CL_DEVICE_VENDOR) << ": "
		<< deviceInfoStr(device_id, CL_DEVICE_NAME) << ": "
		<< deviceInfoStr(device_id, CL_DEVICE_VERSION) << std::endl;
}

void printInfo(cl_platform_id platform_id)
{
	std::cout 
		<< platformInfoStr(platform_id, CL_PLATFORM_VENDOR) << ": "
		<< platformInfoStr(platform_id, CL_PLATFORM_NAME) << ": "
		<< platformInfoStr(platform_id, CL_PLATFORM_VERSION) << std::endl;

	cl_uint num_devices = 0;
	clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, nullptr, &num_devices);

	std::cout << "\tFound " << num_devices << " device(s) on this platform";
	if (num_devices > 0)
	{
		std::cout << ":" << std::endl;

		std::vector<cl_device_id> device_ids(num_devices);
		clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, &device_ids[0], nullptr);

		for (auto device_id : device_ids)
		{
			printInfo(device_id);
		}
	}
	else
		std::cout << "." << std::endl;
}

int main()
{
	cl_uint num_platforms = 0;
	clGetPlatformIDs(0, nullptr, &num_platforms);

	std::cout << "Found " << num_platforms << " OpenCL platform(s)";
	if (num_platforms > 0)
	{
		std::cout << ":" << std::endl;
		std::vector<cl_platform_id> platform_ids(num_platforms);
		clGetPlatformIDs(num_platforms, &platform_ids[0], nullptr);

		for (auto platform_id : platform_ids)
		{
			printInfo(platform_id);
		}
	}
	else
	{
		std::cout << "." << std::endl;
	}

	return 0;
}
