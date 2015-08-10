import sys
import os
import shlex
import subprocess

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
    subprocess.call('doxygen', shell=True)

extensions = ['breathe']
breathe_projects = { 'Nanoshield_Thermocouple': 'xml' }
breathe_default_project = "Nanoshield_Thermocouple"
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = u'Nanoshield_Thermocouple'
copyright = u'2015, Nanoshield_Thermocouple'
author = u'Nanoshield_Thermocouple'
version = '1.0'
release = '1.0'
language = None
exclude_patterns = ['_build']
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'Nanoshield_Thermocoupledoc'
latex_elements = {
}
latex_documents = [
  (master_doc, 'Nanoshield_Thermocouple.tex', u'Nanoshield\_Thermocouple Documentation',
   u'Nanoshield\_Thermocouple', 'manual'),
]
