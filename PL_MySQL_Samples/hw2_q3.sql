DECLARE
  v_max_limit    CONSTANT  NUMBER := 20;
  v_salary employee.salary%TYPE := 500;
  v_count  NUMBER;
BEGIN
  FOR i IN 1..v_max_limit LOOP
      SELECT COUNT(*)
      INTO   v_count
      FROM   employee
      WHERE  salary >= v_salary * (i - 1) AND salary < v_salary * i;
      DBMS_OUTPUT.PUT_LINE(RPAD(TO_CHAR(v_salary * (i - 1), '$99,990.00'), 10) 
                           || ' - ' || TO_CHAR(v_salary * (i) - 0.01, '$99,990.00')
                           || ': ' || v_count);      
  END LOOP;
END;