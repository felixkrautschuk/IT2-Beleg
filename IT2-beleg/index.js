function start() 
            {
                node = document.getElementById("matrix");
                node.parentNode.insertBefore(createTable(document.getElementById("anzahlGleichungen").value, document.getElementById("anzahlUnbekannte").value), node );
            } 
            
            function createTable(row, col, id) 
            {
                var myTable     = document.createElement("table");
                var mytablebody = document.createElement("tbody");
                

                for(var j = 0; j < row; j++) 
                {
                    mycurrent_row = document.createElement("tr");
                    for(var i = 0; i < col; i++) 
                    {
                        mycurrent_cell = document.createElement("td");  
                        var newTextfield = document.createElement("textarea");
                        var atts = document.createAttribute("id");
                        atts.value = i+","+j;
                        newTextfield.setAttributeNode(atts);
                        console.log(atts.value);
                        mycurrent_cell.appendChild(newTextfield);
                        mycurrent_row.appendChild(mycurrent_cell);
                    }
                    mytablebody.appendChild(mycurrent_row);
                }
                myTable.appendChild(mytablebody);
                //myTable.setAttribute("ID", id);
                return myTable;
            }
            
            function test()
            {
                console.log(document.getElementById("0,0").value);
                //console.log(document.getElementById("matrix").children[0].children[1].innerHTML);
                //table.rows[r].cells[c].childNodes[0].value;
                
                //var table = document.getElementById("matrix");
                //console.log(table);
                //var row = table.getElementsByTagName("tr");
                //console.log(row);
                //console.log(row.cells[0].innerHTML);
                //console.log(row[1].value);
               // console.log(document.getElementById("matrix").children[1].val);
            }