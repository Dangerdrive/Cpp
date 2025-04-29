import os

def read_project_files(directory):
    project_context = ""
    # Define file extensions for C++ files
    cpp_extensions = {".cpp", ".h", ".hpp", ".cxx", ".cc", ".hh"}

    for root, _, files in os.walk(directory):
        for file in files:
            # Check if the file has a C++ extension
            if any(file.endswith(ext) for ext in cpp_extensions):
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8") as f:
                    project_context += f"### File: {file}\n"
                    project_context += f.read() + "\n\n"
    return project_context

# Specify the path to your C++ project
project_directory = "."
context = read_project_files(project_directory)

# Print or use the context as needed
print(context)