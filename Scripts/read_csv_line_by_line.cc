ifstream file;

stringstream line_ss;

bool line_fail;

read_csv_file_line_by_line (string fileName)
{
  file (fileName);
  file.seekg (0, ios::end);
  length =file.tellg();
  file.seekg (0, ios::beg);

  lastTime = time(NULL);

  while (file.good())
    {
      getline(file,line);

      currentTime = time(NULL);
      if ((currentTime - lastTime >= 30))
	{
	  current_loc = file.tellg();
	  printf("Completed: %.1f%% ", ((double)current_loc/(double)length)*100);
	  printf("processing line number %llu of %llu ",current_loc,length);
	  printf("with %.0f minutes elapsed\n",currentTime%60);
	  lastTime = currentTime;
	}

      line_ss(line);
      int i = 1;

      line_fail = false;
      while (line_ss.good() && !line_fail)
	{
	  getline(line_ss, value, ',');
	  
	  stringstream value_ss(value);
	  switch(i)
	    {
            case 1: value_ss >> id; break;
            case 2: value_ss >> x; break;
	    case 3: value_ss >> y; break;
	    case 4: value_ss >> z; break;	    
	    case 5: value_ss >> edep; break;
	    case 6: value_ss >> energy; break;
	    case 7: value_ss >> particle_time; break;
	    case 8: value_ss >> particle; break;	   
	    case 9: value_ss >> process; break;
	    case 10: value_ss >> creation_process; break;
	    default: 
	      printf("Error on line %llu\n",current_loc); 
	      id = x = y = z = edep = energy = particle_time = particle = process = creation_process = 0;
	      line_fail = true;
	    }
	  i++;
	}
      return id;
      return x;
    }
}
