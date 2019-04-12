using UnityEngine;
using System.Collections;

public class FiringObjects : MonoBehaviour
{

    public int gunDamage = 1;                                           // Set the number of hitpoints that this gun will take away from shot objects with a health script
    public float fireRate = 0.25f;                                      // Number in seconds which controls how often the player can fire
    [SerializeField]
    public GameObject bullets;

    public Transform gunEnd;                                            // Holds a reference to the gun end object, marking the muzzle location of the gun
    private float nextFire;                                             // Float to store the time the player will be allowed to fire again, after firing
    

    void Update()
    {
        // Check if the player has pressed the fire button and if enough time has elapsed since they last fired
        if (Input.GetButtonDown("Fire1") && Time.time > nextFire)
        {
            // Update the time when our player can fire next
            nextFire = Time.time + fireRate;
			Instantiate(bullets, gunEnd.transform.position, gunEnd.transform.rotation);
            bullets.GetComponent<BulletDamage>().bulletDamage = gunDamage;
        }
        Destroy(bullets, 5.0f);
        
    }
}