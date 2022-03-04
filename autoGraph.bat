@echo off
python "graph_script.py"

git add . 
git commit -m "Updated graph and data"
git push

pause