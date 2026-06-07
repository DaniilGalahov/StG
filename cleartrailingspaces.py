import os

def remove_trailing_spaces_from_file(filepath):
    with open(filepath, 'r') as file:
        lines = file.readlines()

    # Strip trailing spaces/tabs from each line
    cleaned_lines = [line.rstrip() + '\n' for line in lines]

    # Avoid rewriting if no changes
    if lines != cleaned_lines:
        with open(filepath, 'w') as file:
            file.writelines(cleaned_lines)
        print(f"Cleaned: {filepath}")
    else:
        print(f"Unchanged: {filepath}")

def clean_all_source_files(root_dir):
    for dirpath, dirnames, filenames in os.walk(root_dir):
        for filename in filenames:
            if (filename.lower().endswith('.h')
            or filename.lower().endswith('.cpp')
            or filename.lower().endswith('.cs')
            or filename.lower().endswith('.py')):
                filepath = os.path.join(dirpath, filename)
                remove_trailing_spaces_from_file(filepath)

if __name__ == '__main__':
    current_dir = os.path.dirname(os.path.abspath(__file__))
    clean_all_source_files(current_dir)
